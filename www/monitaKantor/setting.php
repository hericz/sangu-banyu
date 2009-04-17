<?php
	require("include.php");
	global $c_id_dept;		$c_id_dept= $_GET['id'];
	global $c_time_refresh;	$c_time_refresh = $_GET['tf'];		//echo "t ref   : " . $c_time_refresh ."<br>";
	global $c_jml_rek_home;	$c_jml_rek_home = $_GET['rek'];		//echo "jml rek : " . $c_jml_rek_home ."<br>";
	require("menu.php");
	//echo $iki;
?>

<div id="setting">
<h2 class="title"><strong>Konfigurasi</strong></h2>
<table id="tabelIsiSetting" border="0" bordercolor="black" cellpadding="1" cellspacing="0" width="500">
	<tr><td width="200">Periode pengambilan data</td><td>: <input type=text id="timeRefresh" size=41 value="<?php echo ($c_time_refresh/1000) . " detik" ?>" title="Periode pengambilan data" onfocus="setStyle(this.id)" onblur="unsetStyle(this.id)" > </td></tr>
	<tr><td>Jumlah data yang ditampilkan </td><td>: <input type=text id="jmlRekHome"  size=41 value="<?php echo $c_jml_rek_home . " data" ?> " title="Jumlah data yang tampil" onfocus="setStyle(this.id)" onblur="unsetStyle(this.id)" > </td></tr>
</table>

<?php
	require("dept.php");		// buat menampilkan daftar perusahaan & departemen
?>

<div id="tombolSetting">
	<button id="btnSimpan" type="button" onclick="ubahSetting()">   Ubah   </button>
	<button id="btnDefault" type="button" onClick="defaultSetting()">Default</button>	
</div>
<div id="ketSetting"><br></div>
</div> <!--   setting -->

<?php
	require("footer.php");
?>
