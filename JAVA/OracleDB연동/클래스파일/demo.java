import java.io.*;
import java.lang.*;
import java.sql.*;

public class demo {
	private Connection conn = null;

	public void connect() {
		try {
			Class.forName( "oracle.jdbc.driver.OracleDriver"); //DriverManager Ŭ������ ���
			conn = DriverManager.getConnection("jdbc:oracle:thin:@localhost:1521:xe", "lim", "lim1234"); //DB ����
			System.out.println( "���������� �ε��Ǿ���" ); 
			Statement stmt = conn.createStatement (); // Statement ����
			ResultSet rset = stmt.executeQuery ("select * from test"); // ������ ����
			System.out.println("�й�\t�̸�\t�ּ�\t��ȭ��ȣ");

			while (rset.next ()) //������ ��� ���
			{
				for(int i = 1 ; i < 5 ; i++)
					System.out.print(rset.getString(i)+ "\t");
				System.out.println();
			} 
 
		} 
		catch( ClassNotFoundException e ) {
			System.out.println( "�ش� ����̹��� ã�� �� �����ϴ�.\n" + e);
		} 
		
		catch( SQLException e) {
			System.out.println( "����Ŭ ���ῡ �����Ͽ����ϴ�.\n" + e);
		}
	}
	
	public static void main( String[] args ){ 
		new demo().connect();
	}
	
}