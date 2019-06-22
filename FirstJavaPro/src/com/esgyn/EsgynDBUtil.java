package com.esgyn;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class EsgynDBUtil {
	static String url = "";
	static String host = "172.16.20.106";
	static String port = "23400";
	static String databaseName = "trafodion";
	static String user = "db__root";
	static String password = "traf123";
	static Connection conn;		
	
	public static Connection getConnection() {
		if(conn != null) {
			return conn;
		}
		try {
			Class.forName("org.trafodion.jdbc.t4.T4Driver");
			url = "jdbc:t4jdbc://" + host + ":" + port + "/:catalog=" + databaseName;
		    conn = DriverManager.getConnection(url, user, password);
		} catch (Exception e) {
			e.printStackTrace();
		}
		return conn;
	}
	
	public static void main(String[] args) {
		url = "jdbc:t4jdbc://" + host + ":" + port + "/:catalog=" + databaseName;
		try {
			Class.forName("org.trafodion.jdbc.t4.T4Driver");
			//url = "jdbc:t4jdbc://" + host + ":" + port + "/:catalog=" + databaseName + ";connectionTimeout=100";
			conn = DriverManager.getConnection(url, user, password);
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		try {
			// System.out.println("---sleep----");
			// Thread.sleep(1000*60*11);
			PreparedStatement stmt = conn.prepareStatement("select * from dual");
			ResultSet rs = stmt.executeQuery();
			// System.out.println("ColumnCount: " + rs.getMetaData().getColumnCount());
			for (int i = 1; i <= rs.getMetaData().getColumnCount(); i++) {
				// System.out.printf(rs.getMetaData().getColumnClassName(i) + " "); 
				System.out.printf("%10s", rs.getMetaData().getColumnLabel(i)); 
			}
			System.out.println();
			while (rs.next()) {
				// System.out.printf("RowNum: " + rs.getRow() + " ");
				for (int i = 1; i <= rs.getMetaData().getColumnCount(); i++) {
					// System.out.printf(rs.getMetaData().getColumnClassName(i) + " "); 
					System.out.printf("%10s", rs.getString(i)); 
				}
				System.out.println();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		// System.out.println(conn);
	}
	
	/*
	 * private static HikariDataSource buildEsgynDBTargetDataSource() throws
	 * Exception { HikariConfig config = new HikariConfig();
	 * config.setMinimumIdle(1);
	 * config.setDriverClassName("org.trafodion.jdbc.t4.T4Driver");
	 * config.setJdbcUrl(url); config.setUsername(user);
	 * config.setPassword(password); config.setConnectionTestQuery("values(1)");
	 * config.setJdbc4ConnectionTest(false); config.setIdleTimeout(60000*3);
	 * config.setConnectionTimeout(60000*3); config.setValidationTimeout(3000);
	 * config.setMaxLifetime(60000*3);
	 * 
	 * HikariDataSource targetDataSource = null; try { targetDataSource = new
	 * HikariDataSource(config); targetDataSource.getConnection(); } catch
	 * (Exception e) { throw new Exception(e); } return targetDataSource; }
	 */
}
