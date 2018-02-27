<%@ page language="java" import="java.util.*,java.sql.*" contentType="text/html; charset=utf-8"%>
<%!
	String user;
	String id;
	String name;
	String pic;
	String price;
	String info;
	String cla;
	String msg;
	Integer quantity;
%>
<%
	user = request.getParameter("user");
	id = request.getParameter("id");
	String connectString = "jdbc:mysql://120.78.73.208:3306/jtb"+ "?autoReconnect=true&useUnicode=true&characterEncoding=UTF-8";
	String users="root";
	String pwd="123456";
	String color="red";
	msg="";
	try{
		Class.forName("com.mysql.jdbc.Driver");
		Connection con=DriverManager.getConnection(connectString, users, pwd);
		Statement stmt=con.createStatement();
		String str = "select * from goods where id = " + id;
		ResultSet rs = stmt.executeQuery(str); 
		while(rs.next()) {
			name = rs.getString("name");
			price = rs.getString("price");
			info = rs.getString("info");
			pic = rs.getString("pic");
			cla = rs.getString("class");
			quantity = rs.getInt("quantity");
		}
		rs.close(); stmt.close(); con.close();
	}
	catch (Exception e){
		msg = e.getMessage();
	}
	StringBuilder table = new StringBuilder();
	try{
		Class.forName("com.mysql.jdbc.Driver");
		Connection con=DriverManager.getConnection(connectString, users, pwd);
		Statement stmt=con.createStatement();
		String str = "select * from comment where good_id =" + id;
		ResultSet rs = stmt.executeQuery(str); 
		table.append("<table border=\"0\">");
		while(rs.next()) {
			table.append(String.format(
								"<tr><td><div style=\"border:solid 2px "+ color +";padding:10px;margin-bottom:10px;border-radius:5px;box-shadow:3px 3px 3px #888888;background:white;color:black;font-weight:bold;\">用户：%s<br/>评论：%s</div></td></tr>",
								rs.getString("comment_from"),
								rs.getString("comment")
							));				
			if(color.equals("yellow")){
				color="red";
			}
			else if(color.equals("HotPink")){
				color="yellow";
			}
			else if(color.equals("green")){
				color="HotPink";
			}
			else if(color.equals("blue")){
				color="green";
			}
			else if(color.equals("red")){
				color="blue";
			}
		}
		table.append("</table>");
		
		rs.close(); stmt.close(); con.close();
	}
	catch (Exception e){
		msg = e.getMessage();
	}
	if(request.getMethod().equalsIgnoreCase("post")){
		if(quantity == 0){
			msg="库存不足，加入失败！";
		}
		else{
			quantity = quantity - 1;
			Class.forName("com.mysql.jdbc.Driver");
			Connection con=DriverManager.getConnection(connectString, users, pwd);
			Statement stmt=con.createStatement();
			try{ 
				String fmt="insert into buy(user,good_id,good_name,good_price,good_class,good_pic) values('%s','%s','%s','%s','%s','%s');";
				String sql = String.format(fmt,user,id,name,price,cla,pic);
				int cnt = stmt.executeUpdate(sql);
				if(cnt > 0)msg = "加入成功！";
			}catch (Exception e){
				msg = e.getMessage();
			}
			try{ 
				String sql="update goods set quantity = " + quantity + " where id = " + id ;
				int cnt = stmt.executeUpdate(sql);
				if(cnt > 0)msg = "加入成功！";
				stmt.close(); con.close();
			}catch (Exception e){
				msg = e.getMessage();
			}
		}
	}
%>
<!DOCTYPE html>
<html>
	<head>
		<meta charset="utf-8">
		<title>商品详情</title>
	</head>
	<script>
		function showq(){
			var obj=document.getElementById("buy");
			obj.value="库存："+<%=quantity%>+"件";
		}
		function hideq(){
			var obj=document.getElementById("buy");
			obj.value="加入购物车";
		}
	</script>
	<style type="text/css">
		
		body {
			position:relative;
			top:-60px;
			width: 100%;
			background: url('images/shopbk2.jpg');
			opacity: 1;
		}
		#good_detail {
			width:700px;
			height: 100%;
			margin: 0 auto;
			padding-top: 100px;
			padding-bottom: 100px;
			line-height: 1.5em;
			position: relative;
		}
		#pic {
			width:400px;
			height: 400px;
			margin: 0 auto;
			border: solid 3px black;
			border-radius: 200px;
			background: white;
		}
		img {
			width:260px;
			height: 260px;
			position: relative;
			top: 60px;
			display: block;
			margin: 0 auto;
		}
		#border1 {
			width:400px;
			border: solid 2px black;
			transform: rotate(25deg);
			position: relative;
			top:-450px;
			left: -200px;
			z-index: -1;
		}
		#border2 {
			width:400px;
			border: solid 2px black;
			transform: rotate(-25deg);
			position: relative;
			top:-100px;
			left: -200px;
			z-index: -1;
		}
		#border3 {
			width:400px;
			border: solid 2px black;
			transform: rotate(-25deg);
			position: relative;
			top:-470px;
			left: 500px;
			z-index: -1;
		}
		#border4 {
			width:400px;
			border: solid 2px black;
			transform: rotate(25deg);
			position: relative;
			top:-110px;
			left: 500px;
			z-index: -1;
		}
		button {
			outline: none;
		}
		#buy {
			position: relative; 
			left: 430px;
			border: solid 2px white;
			border-radius: 5px;
			height: 30px;
			width: 150px;
			background: linear-gradient(to bottom right ,lightskyblue 10%,royalblue 90%);
			box-shadow: 2px 2px 1px grey;
			text-align: center;
			font-family: "微软雅黑";
			color: white;
		}
		#buy:active {
			position: relative; 
			left: 430px;
			border: solid 2px white;
			border-radius: 5px;
			height: 30px;
			width: 150px;
			background: linear-gradient(to bottom right ,royalblue 10%,lightskyblue 90%);
			box-shadow: inset 1px 1px 1px grey;
			text-align: center;
			font-family: "微软雅黑";
			color: white;
		}
		#buy3 {
			position: relative; 
			left: 430px;
			border: solid 2px white;
			border-radius: 5px;
			height: 30px;
			width: 150px;
			background: linear-gradient(to bottom right ,lightskyblue 10%,royalblue 90%);
			box-shadow: 2px 2px 1px grey;
			text-align: center;
			font-family: "微软雅黑";
			color: white;
		}
		#buy3:active {
			position: relative; 
			left: 430px;
			border: solid 2px white;
			border-radius: 5px;
			height: 30px;
			width: 150px;
			background: linear-gradient(to bottom right ,royalblue 10%,lightskyblue 90%);
			box-shadow: inset 1px 1px 1px grey;
			text-align: center;
			font-family: "微软雅黑";
			color: white;
		}
		.info {
			width: 400px;
			margin: 0 auto;
			padding-top: 30px;
		}
		#title1 {
			font-weight: bold;
			display: inline-block;
		}
		#title {
			width: 800px;
			text-align: center;
			color: #000;
			position: relative;
			top: 60px;
			margin: 0 auto;
			font-weight: bold;
			font-family: "微软雅黑";
			font-size: 30px;
		}
		#price {
			float: left;
			width:300px;
			height: 140px;
			position: relative;
			top: 170px;
			left: 40px;
			border-left: solid lightcoral 4px;
			border-top: solid lightcoral 4px;
			background: linear-gradient(to bottom right,rgba(255,255,255,1) 10%,rgba(255,255,255,0) 90%);
			border-top-left-radius: 8px;
			padding: 10px;
			text-align: center;
		}
		#detail {
			float: right;
			width:300px;
			height: 140px;
			position: relative;
			top: 230px;
			right: 90px;
			border-right: solid #FFBB00 4px;
			border-bottom: solid #FFBB00 4px;
			background: linear-gradient(to top left,rgba(255,255,255,1) 10%,rgba(255,255,255,0) 90%);
			border-bottom-right-radius: 8px;
			padding: 10px;
		} 
		#price_tag {
			width: 100px;
			margin: 0 auto;
			text-align: center;
			font-size: 20px;
			color: #FFBB00;
			font-weight: bold;
			margin-bottom: 10px;
		}
		#detail_tag {
			width: 100px;
			margin: 0 auto;
			text-align: center;
			font-size: 20px;
			color: lightcoral;
			font-weight: bold;
			margin-bottom: 10px;
		}
		#purchase {
				height: 700px;
				width: 100%;
				position: absolute;
				top: 0px;
				background: rgba(255,255,255,0.6);
				visibility: hidden;
		}
		#dialog {
				height: 200px;
				width: 450px;
				margin: 0 auto;
				background: #FFF;
				text-align: left;
				border: solid 3px #000;
				border-radius: 15px;
				margin-top: 100px;
		}
		#buy2 {
			position:relative;
			top:90px;
			left:-305px;
		}
		#_price {
			font-weight:bold;
		}
		.a_button:hover {
			background:white;
		}
		table {
			width:700px;
			margin:0 auto;
			position:relative;
			top:-90px;
		}
		#submit_buttom {
			border: solid 2px white;
			border-radius: 5px;
			height: 30px;
			width: 100px;
			background: linear-gradient(to bottom right ,lightskyblue 10%,royalblue 90%);
			box-shadow: 2px 2px 1px grey;
			text-align: center;
			font-family: "微软雅黑";
			color: white;
		}
	</style>
	
	<body>
	<a href="GoodList.jsp?user=<%=user%>" id="buy3" style="z-index:2; width: 50px; height:20px; position:fixed; top:20px; left:20px;border:solid 3px white; border-radius:10px; padding:3px; text-decoration:none; font-size:15px;">返回</a>
		<div id="title" >
				<%=name%>
		</div>
		<div id="price" >
				<div id="price_tag">价格</div>
				<span id="_price">
					<%=price%>
				</span>
		</div>
		<div id="detail" >
				<div id="detail_tag">商品详情</div>
				<span id="_price">
					<%=info%>
				</span>
		</div>
		<div id="good_detail">
			<div id="pic">
				<img src="<%=pic%>" />
				<%if(user.equals("admin")){%>
				
				<%}else{%>
				<form action="goodDetail.jsp?user=<%=user%>&id=<%=id%>"  method="post" name="buy" id="buy2">
					<input id="buy" onmouseover="showq()" onmouseout="hideq()" type="submit" value="加入购物车">
				</form>
				<%}%>
				<div style="position:relative; top:30px; left:0px; font-weight: bold; color: red; text-align:center;"><%=msg%></div>
			</div>
			<br/><br/><br/>
			<div id="border1"> </div>
			<div id="border2"> </div>
			<div id="border3"> </div>
			<div id="border4"> </div>
		</div>
		<div style="position:relative; top:-100px; margin:0 auto; width:700px; text-align:center;">
			<form action="comment.jsp?user=<%=user%>&good_id=<%=id%>" method="post" enctype="application/x-www-form-urlencoded">
				<p style="text-align:left; font-weight:bolder;font-size: 18px;">商品评论：</p>
				<textarea rows="4" cols="80" placeholder="说两句吧..." name="comment"></textarea>
				<input id="submit_buttom" type="submit" value="提交评论">
			</form>
		</div>
		<br/><br/>
		<div>
			<%=table%>
		</div>
		
	</body>
</html>
