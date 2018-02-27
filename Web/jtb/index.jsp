<%@ page language="java" import="java.util.*" contentType="text/html; charset=utf-8"%>

<!DOCTYPE html>
<html lang="zh-cn" >
	<head>
		<title>JTB Shopping Site O(∩_∩)O</title>
		<script language="javascript" type="text/javascript">
		function show_d(){
			var page=document.getElementById("register_d");
			page.style.visibility="visible";
			page.style.opacity="1";
		}
		
		function hide_d(){
			var page=document.getElementById("register_d");
			page.style.visibility="hidden";
			page.style.opacity="0";
		}
		
		function show_l(){
			var page=document.getElementById("register_l");
			page.style.visibility="visible";
			page.style.opacity="1";
		}
		
		function hide_l(){
			var page=document.getElementById("register_l");
			page.style.visibility="hidden";
			page.style.opacity="0";
		}
		
		function show_a(){
			var page=document.getElementById("register_a");
			page.style.visibility="visible";
			page.style.opacity="1";
		}
		
		function hide_a(){
			var page=document.getElementById("register_a");
			page.style.visibility="hidden";
			page.style.opacity="0";
		}
		</script>
		<style type="text/css">   
		    * {margin:0;padding:0;}
		    body {
		    	width:100%;
		    }
			span {
			}
		    #middle_box {
		    	width: 100%;
		    	height: 100%;
		    }
			div#header {
				height: 60px;
				width: auto; 
				font-family: 隶书;
				font-size: 3em;
				color: #FFFFFF;
				font-weight: bold;
				background: transparent;
				border-radius: 5px 5px 0px 0px;
				display: inline-block;
			}
			#main {
				width: 100%;
				height: 700px;
				background: url(images/Mountains_comp.jpg);
				background-size: cover;
				opacity: 1;
				z-index: 5;
			}
			#main2 {
				width: 100%;
				height: 700px;
				background: rgba(0,0,0,1);
				opacity: 0.7;
				position: absolute;
				top: 0px;
			}
			#slides {
				height: 180px;
			}

			#JTB {
				display: inline-block;
				vertical-align: text-bottom;
				font-family: 楷体;
				color: rgba(255,30,30,0.7);
				size: 6em;
				padding-top: 5px;
			}

			#register{
				position: absolute;
				right: 20px;
				top: 10px;
				display: inline-block;
			    font-size: 18px;
			    border: solid 1px #FFF; 
			    border-radius: 5px; 
			    padding: 2px 8px;
				background: rgba(50,35,65,1);
				font-family: 微软雅黑;
				color: #FFF;
			}

			#login{
				position: absolute;
				right: 90px;
				top: 10px;
				display: inline-block;
				font-size: 18px;
				border: solid 1px #FFF; 
			    border-radius: 5px; 
			    padding: 2px 8px;
				background: rgba(50,35,65,1);
				font-family: 微软雅黑;
				color: #FFF;
			}
			
			#login_admin{
				position: absolute;
				right: 160px;
				top: 10px;
				display: inline-block;
				font-size: 18px;
				border: solid 1px #FFF; 
			    border-radius: 5px; 
			    padding: 2px 8px;
				background: rgba(50,35,65,1);
				font-family: 微软雅黑;
				color: #FFF;
			}

			#title1 {
				color: #FFFFFF;
				text-align: center;
				font-size: 80px;
				margin: 0 auto;
				padding-top: 200px;
			}

			#title2 {
				color: #FFFFFF;
				text-align: center;
				font-size: 30px;
				margin: 0 auto;
				padding-top: 20px;
			}

			#footer {
				font-family: "微软雅黑";
				font-weight: bold;
				vertical-align: middle;
				text-align: center;
				height: 30px;
				width: 100%;
				background:gainsboro;
				padding-top: 5px;
			}
			
			#register_d {
				height: 700px;
				width: 100%;
				position: absolute;
				top: 0px;
				background: rgba(255,255,255,0.6);
				visibility: hidden;
				opacity:0;
				transition-property:opacity;
				transition-timing-function:ease;
				transition-duration: 1s;
			}
			
			#registerd_f {
				height: 400px;
				width: 500px;
				margin: 0 auto;
				background: #FFF;
				text-align: left;
				border: solid 3px #000;
				border-radius: 15px;
				margin-top: 100px;
			}
			
			#register_l {
				height: 700px;
				width: 100%;
				position: absolute;
				top: 0px;
				background: rgba(255,255,255,0.6);
				visibility: hidden;
				opacity:0;
				transition-property:opacity;
				transition-timing-function:ease;
				transition-duration: 1s;
			}
			
			#registerl_f {
				height: 200px;
				width: 500px;
				margin: 0 auto;
				background: #FFF;
				text-align: left;
				border: solid 3px #000;
				border-radius: 15px;
				margin-top: 250px;
			}
			
			#register_a {
				height: 700px;
				width: 100%;
				position: absolute;
				top: 0px;
				background: rgba(255,255,255,0.6);
				visibility: hidden;
				opacity:0;
				transition-property:opacity;
				transition-timing-function:ease;
				transition-duration: 1s;
			}
			
			#registera_f {
				height: 200px;
				width: 500px;
				margin: 0 auto;
				background: #FFF;
				text-align: left;
				border: solid 3px #000;
				border-radius: 15px;
				margin-top: 250px;
			}
			
			form {
				width: 300px;
				margin: 0 auto;
				padding: 50px;
			}
		
			.text{font-size: 64px;   
			 font-weight: normal;   
			 text-transform: uppercase;   
			 fill:none;  
			stroke: #B0E0E6;   
			stroke-width: 2px;
			stroke-dasharray: 90 310;
			animation: stroke 6s infinite linear;
			}
			.text-1{stroke: #FFEC8B;
				animation-delay:-1.5s;   
			text-shadow:5px 5px 5px #FFEC8B;
				}
			.text-2{stroke:#AEEEEE;   
				animation-delay:-3s;    
				text-shadow:5px 5px 5px #7FFFD4;
				}
			.text-3{stroke:#EEE0E5;animation-delay:-4.5s;text-shadow:5px 5px 5px #7FFFD4;
				}
			.text-4{stroke:#FFC1C1;animation-delay:-6s;text-shadow:5px 5px 5px #7FFFD4;
				}
			@keyframes stroke { to { stroke-dashoffset: -400;}}
		</style>
	</head>
	<body>
		<div id="middle_box">
			<div id="main">
				
			</div>
			<!-- header -->

			<div id="main2">
				<div id="header">
					<svg width="80%" height="80" style="position: relative; left: 0px; top: 0px;">  
					 <text text-anchor="middle" x="60%" y="80%" class="text text-1" > JTB❤ </text>
					 <text text-anchor="middle" x="60%" y="80%" class="text text-2" > JTB❤</text>   
					 <text text-anchor="middle" x="60%" y="80%" class="text text-3" > JTB❤ </text>
					 <text text-anchor="middle" x="60%" y="80%" class="text text-4" > JTB❤ </text>
					</svg>
					<button id="register" onclick="show_d()">
						注册
					</button>
					<button id="login" onclick="show_l()">
						登录
					</button>
					<button id="login_admin" onclick="show_a()">
						管理
					</button>
				</div>
				<div id="title1">
					欢迎来到 JTB 购物网站！
				</div>
				<div id="title2">
					Enjoy your time !
				</div>
			</div>
		</div>
		<div id="register_d">
			<div id="registerd_f">
				<form action="register.jsp" method="post" enctype="application/x-www-form-urlencoded">
					用户名：&nbsp&nbsp<input type="text" name="user" style="width: 200px;"></br></br>
					密码：&nbsp&nbsp&nbsp&nbsp<input type="password" name="pass" style="width: 200px;"></br></br>
					确认密码：<input type="password" name="conpass" style="width: 200px;"></br></br>
					性别：&nbsp&nbsp&nbsp <input type="radio" name="sex" value="男">男&nbsp&nbsp&nbsp
						  <input type="radio" name="sex" value="女">女&nbsp&nbsp&nbsp
						  <input type="radio" name="sex" value="保密">保密</br></br>
					地址：&nbsp&nbsp&nbsp&nbsp<input type="text" name="addr" style="width: 200px;"></br></br>
					个人信息：<textarea type="text" name="info" style="height: 50px; width: 200px; vertical-align: top;"></textarea></br></br>
					<input name="submit" type="submit" value="提交" style="height: 25px; width: 80px; border: solid 1px #000; border-radius: 3px; margin-right: 30px;float: right; "></br></br>
				</form>
				<button onclick="hide_d()" style="height: 25px; width: 80px; border: solid 1px #000; border-radius: 3px; margin-left: 30px; position: relative; top: -84px; left: 90px; ">返回</button>
			</div>
		</div>
		<div id="register_l">
			<div id="registerl_f">
				<form action="login.jsp" method="post" enctype="application/x-www-form-urlencoded">
					用户名：&nbsp&nbsp<input type="text" name="user" style="width: 200px;"></br></br>
					密码：&nbsp&nbsp&nbsp&nbsp<input type="password" name="pass" style="width: 200px;"></br></br></br>
					<input name="submit" type="submit" value="登录" style="height: 25px; width: 80px; border: solid 1px #000; border-radius: 3px; margin-right: 30px;float: right; "></br></br>
				</form>
				<button onclick="hide_l()" style="height: 25px; width: 80px; border: solid 1px #000; border-radius: 3px; margin-left: 30px; position: relative; top: -84px; left: 90px;">返回</button>
			</div>
		</div>
		<div id="register_a">
			<div id="registera_f">
				<form action="login_admin.jsp" method="post" enctype="application/x-www-form-urlencoded">
					管理员账号：<input type="text" name="user" style="width: 200px;"></br></br>
					密码：&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp<input type="password" name="pass" style="width: 200px;"></br></br></br>
					<input name="submit" type="submit" value="登录" style="height: 25px; width: 80px; border: solid 1px #000; border-radius: 3px; margin-right: 30px;float: right; "></br></br>
				</form>
				<button onclick="hide_a()" style="height: 25px; width: 80px; border: solid 1px #000; border-radius: 3px; margin-left: 30px; position: relative; top: -84px; left: 90px;">返回</button>
			</div>
		</div>
	</body>
	
	<footer>
		<div id="footer">
			Copyright &copy2017-2018 JTB Software Foundation. All Rights Reserved
		</div>
	</footer>
</html>