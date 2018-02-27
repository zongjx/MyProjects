<%@page language="java" contentType="text/html; charset=utf-8"%>
<%@page import="java.io.*,java.util.*,org.apache.commons.io.*,java.sql.*"%>
<%@page import="org.apache.commons.fileupload.*"%>
<%@page import="org.apache.commons.fileupload.disk.*"%>
<%@page import="org.apache.commons.fileupload.servlet.*"%>
<%request.setCharacterEncoding("utf-8");%>
<%!
	String user;
	String good_id;
	String comment;
%>
<%
	user = request.getParameter("user");
	good_id = request.getParameter("good_id");
	comment = request.getParameter("comment");
	String connectString = "jdbc:mysql://120.78.73.208:3306/jtb"+ "?autoReconnect=true&useUnicode=true&characterEncoding=UTF-8";
	String users="root";
	String pwd="123456";
	String msg = "";
	
	Class.forName("com.mysql.jdbc.Driver");
	Connection con = DriverManager.getConnection(connectString,users, pwd);
	Statement stmt = con.createStatement();
	try{ 
		String fmt="insert into comment(good_id,comment_from,comment) values('%s','%s','%s');";
		String sql = String.format(fmt,good_id,user,comment);
		int cnt = stmt.executeUpdate(sql);
		stmt.close(); con.close();
	}catch (Exception e){
		msg = e.getMessage();
	}
	
	response.sendRedirect("goodDetail.jsp?user="+user+"&id="+good_id);
		
		
%>

<!DOCTYPE HTML>
<html>

</html>
