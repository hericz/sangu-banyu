<html><head>
<title>Kirim email</title>
</head><body>

<?php
require("class.phpmailer.php");

//function kirimImel($judul, $isiImel) {
	$mail = new PHPMailer();

	$mail->IsSMTP();                                      // set mailer to use SMTP
	$mail->Host = "daunbiru.com";  // specify main and backup server
	$mail->SMTPAuth = true;     // turn on SMTP authentication
	$mail->Username = "robot@daunbiru.com";  // SMTP username
	$mail->Password = "robot"; // SMTP password

	$mail->From = "robot@daunbiru.com";
	$mail->FromName = "presiden kantor daunbiru";
	$mail->AddAddress("robot@daunbiru.com", "robot");

	$mail->WordWrap = 50;                                 // set word wrap to 50 characters
	$mail->IsHTML(true);                                  // set email format to HTML

	$mail->Subject = "report pintu 20081106-112233";
	//$mail->Subject = $judul;

	$mail->Body    = "<br><br>##pintu depan|Terkancing|200810202%<br>pintu samping|Terbuka|200810032424%<br>pintu mushala|tersingkap|20808141414##<br></body></html>";
	//$mail->Body    = $isiImel;

	$mail->AltBody = "This is the body in plain text for non-HTML mail clients";

	if(!$mail->Send()) {
		echo "Message could not be sent. <p>";
		echo "Mailer Error: " . $mail->ErrorInfo;
		exit;
	}

	echo "Pesan terkirim sukses !";
//}

?>

</body></html>
