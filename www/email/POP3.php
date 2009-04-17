<html><head>
<title>Sedot Email</title>
</head><body>
<?php

require("pop3.class.inc");

$apop_detect = TRUE;    // default = FALSE
$log = TRUE;            // default = FALSE
$log_file = "pop3.class.log"; // must be set when $log = TRUE !!!
$qmailer = FALSE;

//$server = "{mail.daunbiru.com/notls}INBOX";
//$server = "{mail.daunbiru.com:143}INBOX";
$server = "mail.daunbiru.com";
$username = "robot@daunbiru.com";
$password = "robot";

$savetomysql = TRUE;
$savetofile = TRUE;
$delete = TRUE;

$pop3 = new POP3($log,$log_file,$apop_detect);

if($pop3->connect($server)){
    if($pop3->login($username,$password)){
        if(!$msg_list = $pop3->get_office_status()){
            echo $pop3->error;
            return;
        } else {
			echo "connected ! <br>\n";
		}
    }else{
        echo $pop3->error;
        return;
    }
}else{
    echo $pop3->error;
    return;
}

$noob = TRUE;
echo "Jml imel : " . $msg_list["count_mails"] . "<br><br>";
for($i=1;$i<=$msg_list["count_mails"];$i++){
    if(!$header = $pop3->get_top($i)){
        echo $pop3->error;
    }
    // Get Message ID and set $unique_id for save2file()
    $g = 0;
    while(!ereg("</HEADER>",$header[$g])){
		if(eregi("Message-ID",$header[$g])){
			$unique_id = md5($header[$g]);
		}
		$g++;
    }
    unset($g);
	
	if($message = $pop3->get_mail($i, $qmailer)) {
		//echo $message . "<br><br>\n";
		echo "jml array $i : ". count($message);
		for ($j=1; $j<=count($message); $j++) {
			echo $message[$j] . "<br>\n";
		}
	} else {
		echo "gagal $i<br>\n";
	}
	
	/*
	if($get_msg){
		if(!$message = $pop3->get_mail($i, $qmailer)){
			echo $pop3->error;
			$savetofile = FALSE;
			$savetomysql = FALSE;
			$delete = FALSE;
			echo $message . "Pentung<br><br>";
		} else {
			echo $message . "Tidak pentung<br><br>";
		}
		
	} else {
		echo $message . "selaennya <br><br>";
	}
	//*/
	// Send Noob command !!
    if($noop){
        if(!$pop3->noop()){
            echo $pop3->error;
            $noob = FALSE;
        }
    }
	
	if($delete){
        if($pop3->delete_mail($i)){
            echo "Nachricht als gelöscht markiert !!! \r\n <br>";
        }else{
            echo $pop3->error;
        }
    }
}

if($msg_list["count_mails"] == "0"){
    echo "Keine neuen Nachrichten = Tidak ada imel !!";
}

$pop3->close();

?>
</body></html>