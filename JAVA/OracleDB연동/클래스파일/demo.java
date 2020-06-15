import java.io.*;
import java.lang.*;
import java.sql.*;

public class demo {
	private Connection conn = null;

	public void connect() {
		try {
			Class.forName( "oracle.jdbc.driver.OracleDriver"); //DriverManager 클래스에 등록
			conn = DriverManager.getConnection("jdbc:oracle:thin:@localhost:1521:xe", "lim", "lim1234"); //DB 접속
			System.out.println( "성공적으로 로딩되었음" ); 
			Statement stmt = conn.createStatement (); // Statement 생성
			ResultSet rset = stmt.executeQuery ("select * from test"); // 쿼리문 수행
			System.out.println("학번\t이름\t주소\t전화번호");

			while (rset.next ()) //쿼리문 결과 출력
			{
				for(int i = 1 ; i < 5 ; i++)
					System.out.print(rset.getString(i)+ "\t");
				System.out.println();
			} 
 
		} 
		catch( ClassNotFoundException e ) {
			System.out.println( "해당 드라이버를 찾을 수 없습니다.\n" + e);
		} 
		
		catch( SQLException e) {
			System.out.println( "오라클 연결에 실패하였습니다.\n" + e);
		}
	}
	
	public static void main( String[] args ){ 
		new demo().connect();
	}
	
}