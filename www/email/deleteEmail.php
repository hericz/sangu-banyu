<html><head>
<title>Hapus Email</title>
</head><body>
<?php

$server = "{mail.daunbiru.com/notls}INBOX";
//$server = "{mail.daunbiru.com:143}INBOX";
$user = "robot@daunbiru.com";
$pass = "robot";

$mbox = @imap_open($server, $user, $pass)
or die("Gak nyambung ke server, " . imap_last_error());

$check = imap_mailboxmsginfo($mbox);
echo "Messages before delete: " . $check->Nmsgs . "<br />\n";

//imap_delete($mbox, 1);
@imap_delete($mbox,'1:*');

$check = imap_mailboxmsginfo($mbox);
echo "Messages after  delete: " . $check->Nmsgs . "<br />\n";

imap_expunge($mbox);

$check = imap_mailboxmsginfo($mbox);
echo "Messages after expunge: " . $check->Nmsgs . "<br />\n";

imap_close($mbox);

?>

</body></html>
