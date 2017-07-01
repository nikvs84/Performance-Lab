Action()
{
	char super_param[50];
	int x;
	char last_query_param[50];

	lr_start_transaction("_Forum_WEB_03_main_transaction");
	
		lr_start_transaction("_Forum_WEB_03_01_select_topic");
		
		web_reg_save_param_regexp (
		    "ParamName=last_quote",
		    "RegExp=<a href=\"posting.php\\?mode=quote&amp;p=(.+?)\">",
		    "Ordinal=All",
	//	SEARCH_FILTERS,
	//	    "RequestUrl=*/files/index.html",
		LAST );
	
		web_url("{topic_name}", 
			"URL=http://u0351361.isp.regruhosting.ru/{topic}", 
			"TargetFrame=", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Referer=http://u0351361.isp.regruhosting.ru/viewforum.php?f=3", 
			"Snapshot=t6.inf", 
			"Mode=HTML", 
			LAST);
	
		lr_end_transaction("_Forum_WEB_03_01_select_topic",LR_AUTO);		
		
		lr_think_time(10);
		
		lr_start_transaction("_Forum_WEB_03_01_quote");
		
		x = atoi(lr_eval_string("{last_quote_count}"));
		
		sprintf(super_param, "{last_quote_%d}", x);
				
//		last_query_param = lr_eval_string("last_quote", {last_quote_count});
		
		lr_save_string(lr_eval_string(super_param), "quote_id");
		
		
	
		web_url("Reply with quote", 
		        "URL=http://u0351361.isp.regruhosting.ru/posting.php?mode=quote&p={quote_id}",
			"TargetFrame=", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Referer=http://u0351361.isp.regruhosting.ru/{topic}", 
			"Snapshot=t7.inf", 
			"Mode=HTML", 
			LAST);
	
		web_submit_data("posting.php", 
			"Action=http://u0351361.isp.regruhosting.ru/posting.php", 
			"Method=POST", 
			"TargetFrame=", 
			"RecContentType=text/html", 
			"Referer=http://u0351361.isp.regruhosting.ru/posting.php?mode=quote&p={quote_id}&sid={session_id}", 
			"Snapshot=t8.inf", 
			"Mode=HTML", 
			ITEMDATA, 
			"Name=subject", "Value=Re: {topic_name}", ENDITEM, 
			"Name=addbbcode18", "Value=#444444", ENDITEM, 
			"Name=addbbcode20", "Value=0", ENDITEM, 
			"Name=helpbox", "Value=Close all open bbCode tags", ENDITEM, 
			"Name=message", "Value=[quote=\"as\"]Hi![/quote]\r\n{message_body}!", ENDITEM, 
			"Name=mode", "Value=reply", ENDITEM, 
			"Name=sid", "Value={ssid}", ENDITEM, 
			"Name=t", "Value=21", ENDITEM, 
			"Name=post", "Value=Submit", ENDITEM, 
			EXTRARES, 
			"Url=/templates/subSilver/images/cellpic1.gif", "Referer=http://u0351361.isp.regruhosting.ru/viewtopic.php?p={quote_id}", ENDITEM, 
			"Url=/templates/subSilver/images/cellpic3.gif", "Referer=http://u0351361.isp.regruhosting.ru/viewtopic.php?p={quote_id}", ENDITEM, 
			LAST);
	
		lr_end_transaction("_Forum_WEB_03_01_quote",LR_AUTO);
	
	lr_end_transaction("_Forum_WEB_03_main_transaction", LR_AUTO);
	

	return 0;
}