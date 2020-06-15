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
 ����Ŭ �����ͺ��̽� - JAVA ���� ���� �ڵ�
 - GUI ����, ����Ŭ DB ���� �� SQL�� ����Ͽ� ��� ���̺� �ҷ�����
 - Dialog�� ����ؼ� �Է¹��� ��(���ڿ�)�� Ȱ��, '+' ������ ����Ͽ� ������ SQL�� ����� ���ڿ� ������ ����  
 - �ش� ���ڿ��� SQL������ ����Ͽ� ���̺��� ���� �߰��ϰų� ������ �� ���������� �ݿ��Ǵ����� Ȯ���ϰ��� ��
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

	// JFrame ������
	public BankDB() {
		setTitle("Bank DataBase");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container c = getContentPane();
		
		// BorderLayout�� Ȱ���� �� �� �Ϸ� ������Ʈ ��ġ
		c.setLayout(new BorderLayout());
		
		// �ϴܺ� ���� �� ��� ��ư ������Ʈ�� �г�
		JPanel Btn_panel = new JPanel();
		Btn_panel.setLayout(new FlowLayout());
		JButton con = new JButton("����");
		JButton show = new JButton("�� ��� ����");
		JButton show2 = new JButton("���� ���� ������Ȳ ����");
		JButton inse = new JButton("�� �߰�");
		JButton dele = new JButton("�� ����");

		// �гο� ��ư ����
		Btn_panel.add(con);
		Btn_panel.add(show);
		Btn_panel.add(show2);
		Btn_panel.add(inse);
		Btn_panel.add(dele);
		
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
		// DB �д� �� - �� ��Ȳ
		show.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				// DB �б� ����� �Լ� ȣ��
				show_db();
			}
		});
		
		// ��ư �̺�Ʈ ������ (�׼� ������)
		// DB �д� �� - ���� ���� ��Ȳ(��)
		show2.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				// DB �б� ����� �Լ� ȣ��
				show2_db();
			}
		});
		
		// ��ư �̺�Ʈ ������ (�׼� ������)
		// �߰� - ���̾�α� �������� �ϳ��� ����
		inse.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				// DB �б� ����� �Լ� ȣ��
				String SSN = JOptionPane.showInputDialog("�ֹε�Ϲ�ȣ �Է�");
				String name = JOptionPane.showInputDialog("�̸� �Է�");
				String PHONE = JOptionPane.showInputDialog("��ȣ �Է�");
				String ADDR = JOptionPane.showInputDialog("�ּ� �Է�(��/��/��)");
				
				//System.out.println("insert into customer values(" + SSN + ",'" + name + "','" + PHONE + "','" + ADDR + "')");
				String Finn = "insert into customer values(" + SSN + ",'" + name + "','" + PHONE + "','" + ADDR + "')";
				
				
				try {
					Statement stmt2 = conn.createStatement();
					ResultSet rset2 = stmt2.executeQuery(Finn);
				} catch (SQLException e1) {
					e1.printStackTrace();
					state.setText("DB �б� ���� " + e1.toString());
				}
			}
		});
		
		// ��ư �̺�Ʈ ������ (�׼� ������)
		// ���� - ���̾�α� �������� �ϳ��� ����
		// �ֹι�ȣ�� �̸��� �޾Ƽ� ��ġ�ϴ� �� �����ϵ��� ��
		dele.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				// DB �б� ����� �Լ� ȣ��
				String SSN = JOptionPane.showInputDialog("�ֹε�Ϲ�ȣ �Է�");
				//String name = JOptionPane.showInputDialog("�̸� �Է�");
				
				//System.out.println("delete from customer where cstm_ssn = " + SSN);
				String Finn1 = "delete from customer where cstm_ssn = " + SSN;  // + " and cstm_name = " + name;
				
				
				try {
					Statement stmt3 = conn.createStatement();
					ResultSet rset3 = stmt3.executeQuery(Finn1);
				} catch (SQLException e1) {
					e1.printStackTrace();
					state.setText("DB �б� ���� " + e1.toString());
				}
			}
		});
		
		
		// DB ���� ��¿� ��
		state = new JLabel();
		state.setText("Bank DataBase");

		// JFrame�� ��ġ�����ڸ� Ȱ���� ������ ��ġ ����
		add(state, BorderLayout.NORTH);		
		// JScrollPane : ȭ�鿡 �Ѿ ��� ��ũ�ѹٰ� ����
		add(new JScrollPane(table), BorderLayout.CENTER);
		add(Btn_panel, BorderLayout.SOUTH);
		
		
		//ImageIcon �����Ҿ����� = new ImageIcon("�̹���.png");
		ImageIcon imgicon = new ImageIcon("C:\\Users\\Lim\\Downloads\\logo.png");

		//Image �������̹��� = �����Ҿ�����.getImage();  //ImageIcon�� Image�� ��ȯ.
		Image imgresize = imgicon.getImage();
		
		//Image ������̹��� = �������̹���.getScaledInstance(����, ����, java.awt.Image.SCALE_SMOOTH);
		Image imgresized = imgresize.getScaledInstance(300, 600, java.awt.Image.SCALE_SMOOTH);
		
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
			conn = DriverManager.getConnection("jdbc:oracle:thin:@localhost:1521:xe", "limdb", "1234");

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

	public void show_db() {	// �� ��Ȳ�� �о�鿩 ���
		try {
			// Quary
			Statement stmt = conn.createStatement();
			ResultSet rset = stmt.executeQuery("select * from customer");

			//System.out.println("�ֹι�ȣ\t�̸�\t��ȭ��ȣ\t�ּ�");

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
	
	public void show2_db() { // ���� ���� ��Ȳ(���¹�ȣ, �� �̸�, ���� ������ ����/���� ����) ��(��) ���
		try {
			// Quary
			Statement stmt = conn.createStatement();
			ResultSet rset = stmt.executeQuery("select acct_num, cstm_name, bran_name, acct_type from acctstat2");

			//System.out.println("�ֹι�ȣ\t�̸�\t��ȭ��ȣ\t�ּ�");

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
		new BankDB();
	}
}