<html><head>
<title>Sedot Email</title>
</head><body>
<?php

$server = "{mail.daunbiru.com:143/notls}INBOX";
//$server = "{mail.daunbiru.com/notls}INBOX";
//$server = "mail.daunbiru.com";
//$server = "{mail.daunbiru.com:143}INBOX";
$user = "robot@daunbiru.com";
$pass = "robot";

echo "<strong>Tgl : ".date("d-m-Y G:i:s")."</strong><br>\n";

$conn = imap_open($server, $user, $pass)
or die("Gak nyambung ke server");

$headers = imap_headers($conn)
or die("Couldn�t get emails");

header('Content-Type: text/html');
//header('Content-Disposition: inline; filename="Message Source"');
//header('Content-Length: ' . strlen($msg));


$jmlEmail = sizeof($headers);
echo "Ada $jmlEmail di mailbox<br><br>";

//*
//$msg = imap_fetchheader($conn, 1, FT_UID) . "\n" . imap_body($conn, 1, FT_UID);
//   echo $msg;
//*/
//echo "<hr>";
for($i = 1; $i < $jmlEmail+1; $i++) {
//$i = 14;
	$mailHeader = @imap_headerinfo($conn, $i);
	$from = $mailHeader->fromaddress;
	$to = $mailHeader->toaddress;
	$sender = $mailHeader->senderaddress;
	$subject = strip_tags($mailHeader->subject);
	$date = $mailHeader->date;
	echo "Email soko $from, $sender, judul $subject, tgl $date<br>";
}

//echo "<br>";
for($i = 1; $i < $jmlEmail+1; $i++) {

	//$body = nl2br(strip_tags(@imap_body($conn, $id)));
	//$body = strip_tags(@imap_body($conn, $i));
	$body = (@imap_body($conn, $i, FT_PEEK));
	//$body = (@imap_fetchbody($conn, $i));
	//$body = @imap_bodystruct($conn, $i);
	echo "$body";
}
/*
for($i = 1; $i < $jmlEmail+1; $i++) {
	$mailHeader = @imap_headerinfo($conn, $i);
	$from = $mailHeader->fromaddress;
	$to = $mailHeader->toaddress;
	$subject = strip_tags($mailHeader->subject);
	$date = $mailHeader->date;
	echo "Email soko $from, $to, judul $subject, tanggal $date<br>";
}
//*/

?>
</body></html>