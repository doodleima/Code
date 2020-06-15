import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.FlowLayout;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;
/*
* Title : Oracle DB 연동 Test * Date : 2018.10.31
* Purpose : Oracle DB 연동 및 JFrame 사용
*/
public class DBex extends JFrame {
	private Connection conn = null;
	private JLabel state;

	// Table Header Name
	private String colName[] = { "학번", "이름", "주소", "전화번호" };

	// Table Data list (Header data, adding row)
	private DefaultTableModel model = new DefaultTableModel(colName, 0);

	// Create Table
	private JTable table = new JTable(model);
	private String row[] = new String[4];

	// JFrame 생성자
	public DBex() {
		setTitle("DataBase Test");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container c = getContentPane();
		
		// BorderLayout을 활용해 상 중 하로 컴포넌트 위치
		c.setLayout(new BorderLayout());
		
		// 하단부 연결 및 출력 버튼 컴포넌트옹 패널
		JPanel Btn_panel = new JPanel();
		Btn_panel.setLayout(new FlowLayout());
		JButton con = new JButton("Connect");
		JButton show = new JButton("Show");

		// 패널에 버튼 부착
		Btn_panel.add(con);
		Btn_panel.add(show);

		
		// 버튼 이벤트 리스너 (액션 리스너)
		// DB 연결 부
		con.addActionListener(new ActionListener() {
		
			@Override 
			public void actionPerformed(ActionEvent e) {
				// DB 연결 사용자 함수 호출
				connect();
			}
		});
		
		
		// 버튼 이벤트 리스너 (액션 리스너)
		// DB 읽는 부
		show.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				// DB 읽기 사용자 함수 호출
				show_db();
			}
		});

		
		// DB 상태 출력용 라벨
		state = new JLabel();
		state.setText("Oracle DB 연동 테스트");

		// JFrame에 배치관리자를 활용한 각자의 위치 부착
		add(state, BorderLayout.NORTH);		
		// JScrollPane : 화면에 넘어갈 경우 스크롤바가 생김
		add(new JScrollPane(table), BorderLayout.CENTER);
		add(Btn_panel, BorderLayout.SOUTH);
		
		
		//ImageIcon 변경할아이콘 = new ImageIcon("이미지.png");
		ImageIcon imgicon = new ImageIcon("C:\\Users\\Lim\\Downloads\\logo.jpg");

		//Image 변경할이미지 = 변경할아이콘.getImage();  //ImageIcon을 Image로 변환.
		Image imgresize = imgicon.getImage();
		
		//Image 변경된이미지 = 변경할이미지.getScaledInstance(가로, 세로, java.awt.Image.SCALE_SMOOTH);
		Image imgresized = imgresize.getScaledInstance(500, 332, java.awt.Image.SCALE_SMOOTH);
		
		//ImageIcon 변경된아이콘 = new ImageIcon(변경된이미지); //Image로 ImageIcon 생성
		ImageIcon imageicon = new ImageIcon(imgresized); //Image로 ImageIcon 생성
		
		JLabel label = new JLabel(imageicon);
		c.add(label, BorderLayout.WEST);

		setSize(1000, 700);
		setVisible(true);
	}

	public void connect() {
		try {

			// DB 연결
			Class.forName("oracle.jdbc.driver.OracleDriver"); 
			conn = DriverManager.getConnection("jdbc:oracle:thin:@localhost:1521:xe", "lim", "lim1234");

			System.out.println("성공적 로딩");
			state.setText("성공적 연결");

		} catch (ClassNotFoundException e) {
			e.printStackTrace();
			state.setText("드라이버를 찾지 못하였습니다." + e.toString());

		} catch (SQLException e) {
			e.printStackTrace();
			state.setText("DB 연결에 실패하였습니다." + e.toString());
		}
	}

	public void show_db() {
		try {

			// Quary
			Statement stmt = conn.createStatement();
			ResultSet rset = stmt.executeQuery("select * from test order by NUM");

			System.out.println("학번\t이름\t주소\t전화번호");

			while (rset.next()) {
				// row 값 읽기
				for (int i = 1; i < 5; i++) {
					System.out.print(rset.getString(i) + "\t");
					row[i - 1] = rset.getString(i);
				}
				
				System.out.println();

				// JTable에 출력
				model.addRow(row);
			}
			state.setText("DB 읽기 성공");

		} catch (SQLException e) {
			e.printStackTrace();
			state.setText("DB 읽기 실패 " + e.toString());
		}
	}

	public static void main(String[] args) { 
		new DBex();
	}
}