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
* Title : Oracle DB ���� Test * Date : 2018.10.31
* Purpose : Oracle DB ���� �� JFrame ���
*/
public class DBex extends JFrame {
	private Connection conn = null;
	private JLabel state;

	// Table Header Name
	private String colName[] = { "�й�", "�̸�", "�ּ�", "��ȭ��ȣ" };

	// Table Data list (Header data, adding row)
	private DefaultTableModel model = new DefaultTableModel(colName, 0);

	// Create Table
	private JTable table = new JTable(model);
	private String row[] = new String[4];

	// JFrame ������
	public DBex() {
		setTitle("DataBase Test");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container c = getContentPane();
		
		// BorderLayout�� Ȱ���� �� �� �Ϸ� ������Ʈ ��ġ
		c.setLayout(new BorderLayout());
		
		// �ϴܺ� ���� �� ��� ��ư ������Ʈ�� �г�
		JPanel Btn_panel = new JPanel();
		Btn_panel.setLayout(new FlowLayout());
		JButton con = new JButton("Connect");
		JButton show = new JButton("Show");

		// �гο� ��ư ����
		Btn_panel.add(con);
		Btn_panel.add(show);

		
		// ��ư �̺�Ʈ ������ (�׼� ������)
		// DB ���� ��
		con.addActionListener(new ActionListener() {
		
			@Override 
			public void actionPerformed(ActionEvent e) {
				// DB ���� ����� �Լ� ȣ��
				connect();
			}
		});
		
		
		// ��ư �̺�Ʈ ������ (�׼� ������)
		// DB �д� ��
		show.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				// DB �б� ����� �Լ� ȣ��
				show_db();
			}
		});

		
		// DB ���� ��¿� ��
		state = new JLabel();
		state.setText("Oracle DB ���� �׽�Ʈ");

		// JFrame�� ��ġ�����ڸ� Ȱ���� ������ ��ġ ����
		add(state, BorderLayout.NORTH);		
		// JScrollPane : ȭ�鿡 �Ѿ ��� ��ũ�ѹٰ� ����
		add(new JScrollPane(table), BorderLayout.CENTER);
		add(Btn_panel, BorderLayout.SOUTH);
		
		
		//ImageIcon �����Ҿ����� = new ImageIcon("�̹���.png");
		ImageIcon imgicon = new ImageIcon("C:\\Users\\Lim\\Downloads\\logo.jpg");

		//Image �������̹��� = �����Ҿ�����.getImage();  //ImageIcon�� Image�� ��ȯ.
		Image imgresize = imgicon.getImage();
		
		//Image ������̹��� = �������̹���.getScaledInstance(����, ����, java.awt.Image.SCALE_SMOOTH);
		Image imgresized = imgresize.getScaledInstance(500, 332, java.awt.Image.SCALE_SMOOTH);
		
		//ImageIcon ����Ⱦ����� = new ImageIcon(������̹���); //Image�� ImageIcon ����
		ImageIcon imageicon = new ImageIcon(imgresized); //Image�� ImageIcon ����
		
		JLabel label = new JLabel(imageicon);
		c.add(label, BorderLayout.WEST);

		setSize(1000, 700);
		setVisible(true);
	}

	public void connect() {
		try {

			// DB ����
			Class.forName("oracle.jdbc.driver.OracleDriver"); 
			conn = DriverManager.getConnection("jdbc:oracle:thin:@localhost:1521:xe", "lim", "lim1234");

			System.out.println("������ �ε�");
			state.setText("������ ����");

		} catch (ClassNotFoundException e) {
			e.printStackTrace();
			state.setText("����̹��� ã�� ���Ͽ����ϴ�." + e.toString());

		} catch (SQLException e) {
			e.printStackTrace();
			state.setText("DB ���ῡ �����Ͽ����ϴ�." + e.toString());
		}
	}

	public void show_db() {
		try {

			// Quary
			Statement stmt = conn.createStatement();
			ResultSet rset = stmt.executeQuery("select * from test order by NUM");

			System.out.println("�й�\t�̸�\t�ּ�\t��ȭ��ȣ");

			while (rset.next()) {
				// row �� �б�
				for (int i = 1; i < 5; i++) {
					System.out.print(rset.getString(i) + "\t");
					row[i - 1] = rset.getString(i);
				}
				
				System.out.println();

				// JTable�� ���
				model.addRow(row);
			}
			state.setText("DB �б� ����");

		} catch (SQLException e) {
			e.printStackTrace();
			state.setText("DB �б� ���� " + e.toString());
		}
	}

	public static void main(String[] args) { 
		new DBex();
	}
}