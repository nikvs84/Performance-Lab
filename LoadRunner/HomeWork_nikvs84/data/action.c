Action()
{

	web_url("index.php", 
		"URL=http://u0351361.isp.regruhosting.ru/index.php", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=/templates/subSilver/images/cellpic3.gif", ENDITEM, 
		"Url=/templates/subSilver/images/cellpic1.gif", ENDITEM, 
		"Url=/templates/subSilver/images/cellpic2.jpg", ENDITEM, 
		"Url=/favicon.ico", "Referer=", ENDITEM, 
		"Url=http://www.bing.com/favicon.ico", "Referer=", ENDITEM, 
		LAST);

	web_set_sockets_option("SSL_VERSION", "2&3");

	lr_start_transaction("login");

	web_url("iecompatviewlist.xml", 
		"URL=https://iecvlist.microsoft.com/IE11/1479242656000/iecompatviewlist.xml", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/xml", 
		"Referer=", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		LAST);

	web_url("login.php", 
		"URL=http://u0351361.isp.regruhosting.ru/login.php?sid=60f5fdf6ac12c4cc91ecf6776344baf7", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://u0351361.isp.regruhosting.ru/index.php", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=/favicon.ico", "Referer=", ENDITEM, 
		LAST);

	web_submit_data("login.php_2", 
		"Action=http://u0351361.isp.regruhosting.ru/login.php", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://u0351361.isp.regruhosting.ru/login.php?sid=60f5fdf6ac12c4cc91ecf6776344baf7", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value=nikvs84", ENDITEM, 
		"Name=password", "Value=bean", ENDITEM, 
		"Name=redirect", "Value=", ENDITEM, 
		"Name=login", "Value=Log in", ENDITEM, 
		LAST);

	lr_end_transaction("login",LR_AUTO);

	lr_start_transaction("select category");

	web_url("loadtest study 18.06", 
		"URL=http://u0351361.isp.regruhosting.ru/viewforum.php?f=3", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://u0351361.isp.regruhosting.ru/index.php?sid=60f5fdf6ac12c4cc91ecf6776344baf7", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("select category",LR_AUTO);

	lr_start_transaction("select topic");

	web_url("reset1301@mail.ru", 
		"URL=http://u0351361.isp.regruhosting.ru/viewtopic.php?t=13", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://u0351361.isp.regruhosting.ru/viewforum.php?f=3", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("select topic",LR_AUTO);

	lr_start_transaction("quote");

	web_url("Reply with quote", 
		"URL=http://u0351361.isp.regruhosting.ru/posting.php?mode=quote&p=201", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://u0351361.isp.regruhosting.ru/viewtopic.php?t=13", 
		"Snapshot=t7.inf", 
		"Mode=HTML", 
		LAST);

	web_submit_data("posting.php", 
		"Action=http://u0351361.isp.regruhosting.ru/posting.php", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://u0351361.isp.regruhosting.ru/posting.php?mode=quote&p=201", 
		"Snapshot=t8.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=subject", "Value=Re: reset1301@mail.ru", ENDITEM, 
		"Name=addbbcode18", "Value=#444444", ENDITEM, 
		"Name=addbbcode20", "Value=0", ENDITEM, 
		"Name=helpbox", "Value=Close all open bbCode tags", ENDITEM, 
		"Name=message", "Value=[quote=\"as\"]Hi![/quote]\r\nHi-Hi!", ENDITEM, 
		"Name=mode", "Value=reply", ENDITEM, 
		"Name=sid", "Value=60f5fdf6ac12c4cc91ecf6776344baf7", ENDITEM, 
		"Name=t", "Value=13", ENDITEM, 
		"Name=post", "Value=Submit", ENDITEM, 
		EXTRARES, 
		"Url=/templates/subSilver/images/cellpic1.gif", "Referer=http://u0351361.isp.regruhosting.ru/viewtopic.php?p=210", ENDITEM, 
		"Url=/templates/subSilver/images/cellpic3.gif", "Referer=http://u0351361.isp.regruhosting.ru/viewtopic.php?p=210", ENDITEM, 
		LAST);

	lr_end_transaction("quote",LR_AUTO);

	lr_start_transaction("go home");

	web_url("Log out [ nikvs84 ]", 
		"URL=http://u0351361.isp.regruhosting.ru/login.php?logout=true&sid=60f5fdf6ac12c4cc91ecf6776344baf7", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://u0351361.isp.regruhosting.ru/viewtopic.php?p=210", 
		"Snapshot=t9.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("go home",LR_AUTO);

	return 0;
}