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
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;
/*
 오라클 데이터베이스 - JAVA 연동 위한 코드
 - GUI 구현, 오라클 DB 접속 후 SQL문 사용하여 뷰와 테이블 불러오기
 - Dialog를 사용해서 입력받은 값(문자열)을 활용, '+' 연산자 사용하여 완전한 SQL문 만들어 문자열 변수에 저장  
 - 해당 문자열을 SQL문으로 사용하여 테이블에서 값을 추가하거나 제거한 후 성공적으로 반영되는지를 확인하고자 함
*/
public class BankDB extends JFrame {
	private Connection conn = null;
	private JLabel state;

	// Table Header Name
	private String colName[] = { "NUMBER", "NAME", "PHONE/BRAN_NAME", "ADDR/TYPE" };

	// Table Data list (Header data, adding row)
	private DefaultTableModel model = new DefaultTableModel(colName, 0);

	// Create Table
	private JTable table = new JTable(model);
	private String row[] = new String[4];

	// JFrame 생성자
	public BankDB() {
		setTitle("Bank DataBase");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container c = getContentPane();
		
		// BorderLayout을 활용해 상 중 하로 컴포넌트 위치
		c.setLayout(new BorderLayout());
		
		// 하단부 연결 및 출력 버튼 컴포넌트옹 패널
		JPanel Btn_panel = new JPanel();
		Btn_panel.setLayout(new FlowLayout());
		JButton con = new JButton("연결");
		JButton show = new JButton("고객 명단 보기");
		JButton show2 = new JButton("고객별 계좌 개설현황 보기");
		JButton inse = new JButton("고객 추가");
		JButton dele = new JButton("고객 삭제");

		// 패널에 버튼 부착
		Btn_panel.add(con);
		Btn_panel.add(show);
		Btn_panel.add(show2);
		Btn_panel.add(inse);
		Btn_panel.add(dele);
		
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
		// DB 읽는 부 - 고객 현황
		show.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				// DB 읽기 사용자 함수 호출
				show_db();
			}
		});
		
		// 버튼 이벤트 리스너 (액션 리스너)
		// DB 읽는 부 - 계좌 개설 현황(뷰)
		show2.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				// DB 읽기 사용자 함수 호출
				show2_db();
			}
		});
		
		// 버튼 이벤트 리스너 (액션 리스너)
		// 추가 - 다이얼로그 형식으로 하나씩 받음
		inse.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				// DB 읽기 사용자 함수 호출
				String SSN = JOptionPane.showInputDialog("주민등록번호 입력");
				String name = JOptionPane.showInputDialog("이름 입력");
				String PHONE = JOptionPane.showInputDialog("번호 입력");
				String ADDR = JOptionPane.showInputDialog("주소 입력(도/시/군)");
				
				//System.out.println("insert into customer values(" + SSN + ",'" + name + "','" + PHONE + "','" + ADDR + "')");
				String Finn = "insert into customer values(" + SSN + ",'" + name + "','" + PHONE + "','" + ADDR + "')";
				
				
				try {
					Statement stmt2 = conn.createStatement();
					ResultSet rset2 = stmt2.executeQuery(Finn);
				} catch (SQLException e1) {
					e1.printStackTrace();
					state.setText("DB 읽기 실패 " + e1.toString());
				}
			}
		});
		
		// 버튼 이벤트 리스너 (액션 리스너)
		// 삭제 - 다이얼로그 형식으로 하나씩 받음
		// 주민번호와 이름만 받아서 일치하는 행 삭제하도록 함
		dele.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				// DB 읽기 사용자 함수 호출
				String SSN = JOptionPane.showInputDialog("주민등록번호 입력");
				//String name = JOptionPane.showInputDialog("이름 입력");
				
				//System.out.println("delete from customer where cstm_ssn = " + SSN);
				String Finn1 = "delete from customer where cstm_ssn = " + SSN;  // + " and cstm_name = " + name;
				
				
				try {
					Statement stmt3 = conn.createStatement();
					ResultSet rset3 = stmt3.executeQuery(Finn1);
				} catch (SQLException e1) {
					e1.printStackTrace();
					state.setText("DB 읽기 실패 " + e1.toString());
				}
			}
		});
		
		
		// DB 상태 출력용 라벨
		state = new JLabel();
		state.setText("Bank DataBase");

		// JFrame에 배치관리자를 활용한 각자의 위치 부착
		add(state, BorderLayout.NORTH);		
		// JScrollPane : 화면에 넘어갈 경우 스크롤바가 생김
		add(new JScrollPane(table), BorderLayout.CENTER);
		add(Btn_panel, BorderLayout.SOUTH);
		
		
		//ImageIcon 변경할아이콘 = new ImageIcon("이미지.png");
		ImageIcon imgicon = new ImageIcon("C:\\Users\\Lim\\Downloads\\logo.png");

		//Image 변경할이미지 = 변경할아이콘.getImage();  //ImageIcon을 Image로 변환.
		Image imgresize = imgicon.getImage();
		
		//Image 변경된이미지 = 변경할이미지.getScaledInstance(가로, 세로, java.awt.Image.SCALE_SMOOTH);
		Image imgresized = imgresize.getScaledInstance(300, 600, java.awt.Image.SCALE_SMOOTH);
		
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
			conn = DriverManager.getConnection("jdbc:oracle:thin:@localhost:1521:xe", "limdb", "1234");

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

	public void show_db() {	// 고객 현황을 읽어들여 출력
		try {
			// Quary
			Statement stmt = conn.createStatement();
			ResultSet rset = stmt.executeQuery("select * from customer");

			//System.out.println("주민번호\t이름\t전화번호\t주소");

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
	
	public void show2_db() { // 계좌 개설 현황(계좌번호, 고객 이름, 은행 지점과 적금/예금 여부) 을(를) 출력
		try {
			// Quary
			Statement stmt = conn.createStatement();
			ResultSet rset = stmt.executeQuery("select acct_num, cstm_name, bran_name, acct_type from acctstat2");

			//System.out.println("주민번호\t이름\t전화번호\t주소");

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
		new BankDB();
	}
}