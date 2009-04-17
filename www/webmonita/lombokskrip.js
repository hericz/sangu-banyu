// 	Taun baru di Helwin, lombok timur
//	File javascript ajax
//	Thunnel buat nyedot data dari database monita
//	versi 1.0.0


//var waktu = 5;
var jmlData;
var awal = 0;
var AP = 3;		// jml angka penting dalam desimal
var toM, toI, toH;
var timeRefresh;// = 5000;		// tiap 5 detik
var noJdlTbl;
var arHistori = [ {no: "0", nilai: 4460, time: "010203"}, {no: "1", nilai: 4486, time: "200302"}, {no: "2", nilai: 4410, time: "010203"}, {no: "3", nilai: 4500, time: "200302"}, {no: 4, nilai: 4450, time: "200302"} ];	// buat nyimpen data hostori
var arHome	  = [];
var arParam   = [];
var arPrsh = [];
var menu;
var noboard = 2;
var tolMenit = 1;
var jmlRekHome;
var jmlKW = 8;
var jmlTitik = 13;
var noNoBoard = 1;
var masuk = 0;
var debug = 0;
var bulan = ["Jan","Feb","Mar","Apr","Mei","Jun","Jul","Agt","Sep","Okt","Nov","Des"];
var tlCookies = 365;

var peta;
//var limit = 10;

var noAlat;		//  diesel, kompresor, turbo
var noSubAlat;	// Sulzer #1, 
var id_dept;	// PLTD Paokmotong

//dojo.require("dojox.charting.Chart2D");
dojo.require("dojo.collections.Store");
dojo.require("dojo.charting.Chart");
dojo.require("dojo.html.display");
dojo.require("dojo.widget.*");
//dojo.require("dojo.widget.TaskBar");
//dojo.require("dojo.widget.LayoutContainer");
dojo.require("dojo.widget.FloatingPane");
dojo.require("dojo.widget.ResizeHandle");

var months  = new Array("Januari", "Febuari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember");
var calDays = new Array("Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu");

var idReq            = getXmlHttpRequestObject();
var idPLTDReq        = getXmlHttpRequestObject();
var menuAtasReq      = getXmlHttpRequestObject();
var menuKiriAtasReq  = getXmlHttpRequestObject();
var menuKiriBawahReq = getXmlHttpRequestObject();
var tahuTabelReq	 = getXmlHttpRequestObject();
var isiHomeReq		 = getXmlHttpRequestObject();
var isiMesinReq      = getXmlHttpRequestObject();
var isiReq           = getXmlHttpRequestObject();
var historiReq       = getXmlHttpRequestObject();
var opsiHistoriReq	 = getXmlHttpRequestObject();

function getXmlHttpRequestObject() {
	if (window.XMLHttpRequest) {
		return new XMLHttpRequest();
		//return XMLHttpRequest();
	} else if(window.ActiveXObject) {
		return new ActiveXObject("Microsoft.XMLHTTP");
		//return ActiveXObject("Microsoft.XMLHTTP");
	} else {
		document.getElementById('p_status').innerHTML = 'Status: Tidak bisa membuat objek XmlHttpRequest.  Segera upgrade browser Anda.';
	}
}

function awalProses() {
	masukHome(); 
	if (masuk) {
		menuAtas(noAlat);
	}
}

dojo.addOnLoad(mulai);

function startup() {
	init();
	isiPilihHistori();
	//setCookiesDefault();
	cekCookies();
	//alert("no ini");
	Identitas();	
	mongsoSaiki();
	awalProses();
	//var menu = cssMenuAtas("Home",999) + " </li></ul>";
	document.getElementById('menuatas').innerHTML = menuHomeSaja();
	//document.getElementById('thn').innerHTML = thnBawah();
}

function mulai() {
	Identitas();
	dojo.html.hide('spyPLTD');
	dojo.html.setDisplay('spyPLTD', false);
}

function menuHomeSaja() {
	//return (cssMenuAtas("Home",999) + " </li></ul>");
	//return (cssMenuAtas("Home",999) + " </li></ul>");
	return (cssMenuAtas("Home",999) + " </li>" + cssMenuAtas("Setting",999) + " </li></ul>");
}

function mongsoSaiki() {
	setTimeout( "mongsoSaiki()", 1000 );
	var t    = new Date();
	var dino = t.getDay();
	var tgl  = t.getDate();
	var bln  = t.getMonth();		// januari = 0
	var thn  = t.getFullYear();
	var jam  = t.getHours();
	var mnt  = t.getMinutes();
	var dtk  = t.getSeconds();
	document.getElementById('mongso').innerHTML = calDays[dino] + ", " + tgl + " " + months[bln] + " " + thn + " " + jam + ":" + t0(mnt) + ":" + t0(dtk);
}

function menuAtas(jenis) {
	var str;
	noAlat = jenis;
	//document.getElementById('menuatas').innerHTML = "Home";
	
	//*
	if (menuAtasReq.readyState == 4 || menuAtasReq.readyState == 0) {
		str = "getData.php?fetchMenu=1";
		str+= "&noAlat=" + noAlat;
		str+= "&id_dept=" + id_dept;
		menuAtasReq.open("GET", str, true);
		menuAtasReq.onreadystatechange = handleMenuAtas; 
		menuAtasReq.send(null);
	}
	//*/
}

function handleMenuAtas() {
	//var status = 0;
	if (menuAtasReq.readyState == 4) {
		var tempMenu = "";
		var akhir = 0;
		var xmldoc = menuAtasReq.responseXML;
		var message_nodes = xmldoc.getElementsByTagName("pesan"); 
		var n_messages = message_nodes.length;

		//document.getElementById('menuatas').innerHTML += cssMenuAtas("Home",999);// + akhirHTMLmenuAtas(0);
		menu = cssMenuAtas("Home",999);// + akhirHTMLmenuAtas(0);
		//document.getElementById('menuatas').innerHTML += cssMenuAtas("Semua saja",999);			
		//menu += akhirHTMLmenuAtas(status);
		status = 0;
		menu += akhirHTMLmenuAtas(status);
		if (debug) {
			menu += cssMenuAtas("Cek",999);
			menu += akhirHTMLmenuAtas(status);
		}
		
		menu += cssMenuAtas("Setting",999);
		status = 0;
		for (i = 0; i < n_messages; i++) {
			var alat = message_nodes[i].getElementsByTagName("alat");
			var ideq = message_nodes[i].getElementsByTagName("ideq");
			
			if (alat[0].firstChild.nodeValue != tempMenu) {		// jika tidak sama, bikin menu
				//document.getElementById('menuatas').innerHTML += akhirHTMLmenuAtas(0);
				menu += akhirHTMLmenuAtas(status);
				tempMenu = alat[0].firstChild.nodeValue;
				//document.getElementById('menuatas').innerHTML += cssMenuAtas(alat[0].firstChild.nodeValue, ideq[0].firstChild.nodeValue);
				if (i == (n_messages-noNoBoard)) { akhir = 1 };
				menu += cssMenuAtas(alat[0].firstChild.nodeValue, ideq[0].firstChild.nodeValue, akhir);
			}
			var kelp  = message_nodes[i].getElementsByTagName("kelp");
			var jenis = message_nodes[i].getElementsByTagName("jenis");
			status = 1;
			//document.getElementById('menuatas').innerHTML += cssSubMenuAtas(kelp[0].firstChild.nodeValue, ideq[0].firstChild.nodeValue, jenis[0].firstChild.nodeValue);
			
			menu += cssSubMenuAtas(kelp[0].firstChild.nodeValue, ideq[0].firstChild.nodeValue, jenis[0].firstChild.nodeValue);
		}
		//*/
		//document.getElementById('menuatas').innerHTML += akhirHTMLmenuAtas(1);
		menu += akhirHTMLmenuAtas(2);
		document.getElementById('menuatas').innerHTML = menu;
		//}
	}
}
function akhirHTMLmenuAtas(status) {
	var seni;
	if (status == 0)
		seni = " </li> ";	//  <br>
	else if (status == 1)
		seni = " </li> </ul>";  // <br>
		//seni = " </ul> </li>";  // <br>
	else
		seni = " </ul> </li> </ul>";  // <br>
	return seni;
}

function cssMenuAtas(menu, idmenu, status) {
	var seni;
//	seni = '<a href="#" onclick="menuKiriAtas(' + idmenu + ')" title="' + menu + '">' + menu + '</a>';
	if (menu == "Home" || menu == "Semua saja") {
		seni = ' <ul id="nav"> <li> <a href="#" title="' + menu + '" onclick="masukHome()">' + menu + '</a>';
		//seni = ' <ul id="nav"> <li> <h2> <a href="#" title="' + menu + '" onclick="masukHome()">' + menu + '</a> </h2>';
		//seni = ' <ul> <li> <h2> <a href="#" onclick="menuKiriAtas(' + idmenu + ')" title="' + menu + '">' + menu + '</a> </h2>';
	} else if (menu == "Setting") {
		seni = ' <li> <a href="#" title="' + menu + '" onclick="masukSetting(0)">' + menu + '</a>';
	} else if (menu == "Cek") {
		seni = ' <li> <a href="#" title="' + menu + '" onclick="masukCek()">' + menu + '</a>';
	} else {
		if (status)
			seni = ' <li id="noboard"> <a href="#" onclick="klikMenuAtas(' + idmenu + ')" title="' + menu + '">' + menu + "</a> <ul> "; // <br> &lt;ul&gt;
			//seni = ' <li id="noboard"> <h2> <a href="#" onclick="klikMenuAtas(' + idmenu + ')" title="' + menu + '">' + menu + "</a> </h2> <ul> "; // <br> &lt;ul&gt;
		else
			seni = ' <li> <a href="#" onclick="klikMenuAtas(' + idmenu + ')" title="' + menu + '">' + menu + "</a> <ul> "; // <br> &lt;ul&gt; 
			//seni = ' <li> <h2> <a href="#" onclick="klikMenuAtas(' + idmenu + ')" title="' + menu + '">' + menu + "</a> </h2> <ul> "; // <br> &lt;ul&gt; 
		//seni = ' <ul> <li> <h2> <a href="#" onclick="tahuIsiMesin(' + idmenu + ',' + idmenu + ')" title="' + menu + '">' + menu + "</a> </h2> "; // <br> &lt;ul&gt; 
		//tahuIsiMesin(id_dept, idmenu);
		//cssTahuIsi(idnama, idnilai, idtitik);
		//seni = ' &lt;ul&gt; &lt;li&gt; h2 <a href="#" onclick="menuKiriAtas(' + idmenu + ')" title="' + menu + '">' + menu + "</a> /h2 &lt;ul&gt; "; // <br> &lt;ul&gt; 
		//seni = '<a href="#" onclick="menuKiriAtas(' + idmenu + ')" title="' + menu + '">' + menu + '</a>';
	}
	return seni;
}

function klikMenuAtas(idmenu) {
	menuKiriAtas(idmenu);
	tahuIsiMesin(id_dept, idmenu);
}

function masukCek() {
	stopTimer();
	var setting = document.getElementById('tahuIsi');
	setting.innerHTML  = "timeRefresh = " + timeRefresh + "<br>";
	setting.innerHTML += "jmlRekHome = " + jmlRekHome  + "<br>";
	//alert(timeRefresh);
}

function cssSubMenuAtas(submenu, idmenu, idsubmenu) {
	var seni;
	//seni = '<li> <a href="#" onclick="tesSubMenu(' + idmenu + ',' + idsubmenu + ')" title="' + submenu + '">' + submenu + '</a> </li>';	//  <br>
	seni = '<li> <a href="#" onclick="tesSubMenu(' + idmenu + ',' + idsubmenu + ')" title="' + submenu + '">' + submenu + '</a> </li>';	//  <br>
	return seni;
}

function tesSubMenu(idmenu, idsubmenu) {
		clearDetail();
		menuKiriAtas(idmenu);
		tahuIsi(id_dept, idmenu, idsubmenu);	//tahuIsi(13, 28, 1);
		noAlat = idmenu;
		noSubAlat = idsubmenu;
}

function menuKiriAtas(jenis) {
	var str;
	noSubAlat = jenis;
	if (menuKiriAtasReq.readyState == 4 || menuKiriAtasReq.readyState == 0) {
		//document.getElementById('menuEquip').innerHTML = "Kiri atas : <br>";
		str = "getData.php?fetchMenu=4";
		str+= "&noAlat=" + noAlat;
		str+= "&noSubAlat=" + noSubAlat;
		str+= "&id_dept=" + id_dept;
		menuKiriAtasReq.open("GET", str, true);
		menuKiriAtasReq.onreadystatechange = handleMenuKiriAtas; 
		menuKiriAtasReq.send(null);
	}
}
//*
function handleMenuKiriAtas() {		// SubAlat, kelompok pengukuran
	if (menuKiriAtasReq.readyState == 4) {		
		var xmldoc = menuKiriAtasReq.responseXML;
		var message_nodes = xmldoc.getElementsByTagName("pesan"); 
		var n_messages = message_nodes.length;		
		//document.getElementById('jmlNode').value=n_messages;
		if (n_messages > 0) {
			var menuX = document.getElementById('menuEquip');
			menuX.style.marginTop = "0px";
			menuX.style.marginBottom = "10px";
			menuX.style.marginRight = "60px";
			menuX.style.border = "1px solid #8E8E8E";
			menuX.style.padding = "10px";
			menuX.innerHTML = '<b>Kelompok pengukuran<br></b>';
			for (i = 0; i < n_messages; i++) {
				var klp   = message_nodes[i].getElementsByTagName("kelp");
				var ideq  = message_nodes[i].getElementsByTagName("ideq");
				var jenis = message_nodes[i].getElementsByTagName("jenis");
				//document.getElementById('menuEquip').innerHTML += cssMenuKiriAtas(klp[0].firstChild.nodeValue);
				cssMenuKiriAtas(klp[0].firstChild.nodeValue, ideq[0].firstChild.nodeValue, jenis[0].firstChild.nodeValue);
			}
		}
	}
}

function cssMenuKiriAtas(menu, id_alat, id_subAlat) {		// menu kiri atas : kelompok titik ukur
	var seni;
	//seni = '<li><a href="#" onclick="gantiFooter(' + ideq + ')" title="' + menu + '">' + menu + '</a></li>';
	seni = '<a href="#" onclick="tahuIsi(' + id_dept + ',' + id_alat + ',' + id_subAlat + ',1)" title="' + menu + '">' + menu + '</a><br>';
	//tahuIsi(id_dept, idmenu, idsubmenu);
	//document.getElementById('footer').innerHTML = "nilai : " + ideq;
	document.getElementById('menuEquip').innerHTML += seni; 
	//return seni;
}

function menuKiriBawah() {
	var str;
	if (menuKiriBawahReq.readyState == 4 || menuKiriBawahReq.readyState == 0) {
		str = "getData.php?fetchMenu=3";
		str+= "&id_dept=" + id_dept;
		menuKiriBawahReq.open("GET", str, true);
		menuKiriBawahReq.onreadystatechange = handleMenuKiriBawah; 
		menuKiriBawahReq.send(null);
	}
}

function handleMenuKiriBawah() {
	if (menuKiriBawahReq.readyState == 4) {		
		var xmldoc = menuKiriBawahReq.responseXML;
		var message_nodes = xmldoc.getElementsByTagName("pesan"); 
		var n_messages = message_nodes.length;		

		if (n_messages > 0) {
			//document.getElementById('menukiriBawah').innerHTML = "Peralatan PLTD : <br>";
			for (i = 0; i < n_messages; i++) {
				var alat = message_nodes[i].getElementsByTagName("alat");
				var iden = message_nodes[i].getElementsByTagName("iden");
				document.getElementById('menukiriBawah').innerHTML += cssMenuKiriBawah(alat[0].firstChild.nodeValue, iden[0].firstChild.nodeValue) + "<br>";
			}
		}
	}
}

function cssMenuKiriBawah(menu,jenis) {
	var seni;
	seni = '<a href="#" onclick="menuAtas(' + jenis + ')" title="Mesin ' + menu + '">' + menu + '</a>';
	return seni;
}

function tahuTabel(dept, menu) {
	var str;
	if (tahuTabelReq.readyState == 4 || tahuTabelReq.readyState == 0) {
		//document.getElementById('menuEquip').innerHTML = "Kiri atas : <br>";
		str = "getData.php?fetchMenu=4";
		//str+= "&noAlat=" + noAlat;
		//str+= "&noSubAlat=" + noSubAlat;
		//str+= "&id_dept=" + id_dept;
		//tahuTabelReq.open("GET", str, true);
		//tahuTabelReq.onreadystatechange = handleMenuKiriAtas; 
		//tahuTabelReq.send(null);
	}	
}

function init() {
	noAlat  = 0;		// 0 = diesel, generator
	noSubAlat = 29;
	id_dept = 3;		// init masuk ke cookies, pelajari << otomatis dari tabel departemen
	waktu = 5;
	timeRefresh = 5000;
	jmlRekHome = 21;
	//AP = 3;
	//document.getElementById('EquipNow').innerHTML = "csdsds";
}

function Identitas() {
	var str;
	//document.getElementById('identitas').innerHTML = "<h1>Monita 1.1</h1>";
	document.getElementById('identitas').innerHTML = "<h1>Online Monitoring System</h1>";
	if (idReq.readyState == 4 || idReq.readyState == 0) {
		str = "getData.php?fetchMenu=2";
		//str+= "&id_dept=" + id_dept;
		idReq.open("GET", str, true);
		idReq.onreadystatechange = handleReceiveID; 
		idReq.send(null);
	}
}

function handleReceiveID() {
	arPrsh = [];
	var objPrsh = {};
	if (idReq.readyState == 4) {
		var xmldoc = idReq.responseXML;
		var message_nodes = xmldoc.getElementsByTagName("pesan"); 
		var n_messages = message_nodes.length;
		//document.getElementById('identitas').innerHTML += "<h1>TRewsinf ...</h1>";

		if (n_messages == 1) {
			//alert("cuma 1");
			var idDp = message_nodes[0].getElementsByTagName("idDp");
			var nmDp = message_nodes[0].getElementsByTagName("nmDp");
			var nmPr = message_nodes[0].getElementsByTagName("nmPr");
			var Almt = message_nodes[0].getElementsByTagName("Almt");
			document.getElementById('identitas').innerHTML += "<h1>" + nmDp[0].firstChild.nodeValue + "</h1>";
			document.getElementById('sikil').innerHTML += nmDp[0].firstChild.nodeValue + ", " + nmPr[0].firstChild.nodeValue;
			document.getElementById('spyPLTD').innerHTML = "";
			document.getElementById('isiPane').innerHTML = "";
			//dojo.html.hide('spyPLTD');
			dojo.html.setDisplay('spyPLTD', false);
		} else {
			for (i = 0; i < n_messages; i++) {
				var idDp = message_nodes[i].getElementsByTagName("idDp");
				var nmDp = message_nodes[i].getElementsByTagName("nmDp");
				var nmPr = message_nodes[i].getElementsByTagName("nmPr");
				var Almt = message_nodes[i].getElementsByTagName("Almt");
				//objPrsh = { id: idDp[0].firstChild.nodeValue, nmDp: nmDp[0].firstChild.nodeValue, nmPr: nmPr[0].firstChild.nodeValue, Almt: Almt[0].firstChild.nodeValue };
				objPrsh = { id: idDp[0].firstChild.nodevalue, nmDp: nmDp[0].firstChild.nodeValue, nmPr: nmPr[0].firstChild.nodeValue };
				arPrsh.push(objPrsh);
			}
			document.getElementById('identitas').innerHTML += "<h1>daunbiru sejahtera</h1>";
			
		}
		/*
		for (i = 0; i < n_messages; i++) {
			var dept = message_nodes[i].getElementsByTagName("dept");
			var prsh = message_nodes[i].getElementsByTagName("prsh");
			
			//document.getElementById('identitas').innerHTML += "<h3>" + prsh[0].firstChild.nodeValue + " " + dept[0].firstChild.nodeValue + "</h3>";
			//document.getElementById('identitas').innerHTML += "<h1>" + prsh[0].firstChild.nodeValue + " " + dept[0].firstChild.nodeValue + "</h1>";
			document.getElementById('identitas').innerHTML += "<h1>" + dept[0].firstChild.nodeValue + "</h1>";
			document.getElementById('sikil').innerHTML += dept[0].firstChild.nodeValue + ", " + prsh[0].firstChild.nodeValue;
			//document.getElementById('identitas').innerHTML += prsh[0].firstChild.nodeValue + "</h2>";
		}
		//*/
	}
}

function footer() {
	document.getElementById('footer').innerHTML = "- Monita, Sistem monitoring Mesin - daunbiruengineering -";
}

function masukSetting(status) {
	stopTimer();
	var jmlRekHome  = getCookie('jmlRekHome');
	var timeRefresh = getCookie('timeRefresh');
	
	if (status == 1) {
		jmlRekHome  = 21;
		timeRefresh = 5000; 
	}
	
	var setting = document.getElementById('tahuIsi');
	//setting.innerHTML = "";
	var judulIsi = '<h2 class="title"><strong>Konfigurasi</strong></h2>';
	setting.innerHTML = judulIsi.bold();
	setting.innerHTML += '<br>';
	setting.innerHTML += '<table id="tabelIsiSetting" border="1" bordercolor="black" cellpadding="1" cellspacing="0" width="500"></table>';
	paramSetting("Periode pengambilan data","timeRefresh", (timeRefresh/1000) + " detik", "tabelIsiSetting");
	paramSetting("Jumlah data yang tampil","jmlRekHome", jmlRekHome, "tabelIsiSetting");
	//paramSetting("Pilih Perusahan :");
	//paramSetting("Jumlah data yang tampil","jmlRekHome","tabelIsiSetting");
	setting.innerHTML += '<br>';

	var ket;
	var jmlPrsh = arPrsh.length;
	var checked = 2;
	//var jmlPrsh = 3;
	var nama = arPrsh[0].nmPr;
	var id   = arPrsh[0].idPr;
	ket  = '<table id="tabelIsiPersh" border="1" bordercolor="black" cellpadding="1" cellspacing="0" width="500">';
	ket += '<tr><td rowspan="' + jmlPrsh  + '">Pilih<br>Perusahaan</td><td>' + radio(checked, id, nama)  + '</td></tr>';
	for (k=1; k<jmlPrsh; k++) {
		ket += '<tr><td>' + radio(checked, arPrsh[k].idPr, arPrsh[k].nmPr) +  '</td></tr>';
	}
	ket += '</table>';
	
	setting.innerHTML += ket;
	setting.innerHTML += '<br>';
	setting.innerHTML += '<input id="btnSimpan" type="button" value="   Ubah   " onclick="ubahSetting()"/>';
	setting.innerHTML += '   ';
	setting.innerHTML += '<input id="btnBatal" type="button" value="Batal" onclick="batalSetting()"/>';
	setting.innerHTML += '   ';
	setting.innerHTML += '<input id="btnDefault" type="button" value="Default" onclick="masukSetting(1)"/>';
	setting.innerHTML += '<br><br><br><div id="ketSetting"></div>';
}

function radio(checked, id, nama) {
	var strCek = "";
	if (id == checked) strCek = "checked";
	//return "tesRadio";
	return '<input type="radio" name="Prsh" value="' + nama + '" ' + strCek + ' > ' + nama;
}

function ubahSetting() {
	var jmlRek = document.getElementById("jmlRekHome");
	var time = document.getElementById("timeRefresh");
	var setting = document.getElementById('ketSetting');
	if (jmlRek.value<2) {
		alert("Jumlah rekaman harus >1 data");
		setting.innerHTML = 'Konfigurasi gagal diubah';
		return 0;
	} else {
		jmlRekHome = jmlRek.value;
		//return 0;
	}
	timeRefresh = parseInt(time.value)*1000;
	//alert(parseInt(timeRefresh.value));
	//alert(jmlRekHome.value);
	setCookie('jmlRekHome', jmlRekHome, 1);
	//setCookie('jmlTitik', 13, 1);
	setCookie('timeRefresh', timeRefresh, 1);
	
	
	setting.innerHTML = 'Konfigurasi berhasil diubah';
	
	var deret = [];
	var obj = {};
	arHome = [];
	
	//*
	for (i=0; i<jmlKW; i++) {
		deret = [];
		for (j=0; j<jmlRekHome; j++) {
			//isi = (i*10+j);
			obj = {no: j, nama:"blavla", nilai:0, waktu:"0"};
			//obj = (i*10)+j;
			deret.push(obj);
			//document.getElementById('tahuIsi').innerHTML  += deret[j].nilai + " ";
		}
		arHome.push(deret);
	}
	
	arParam = [];
	for (i=0; i<jmlTitik; i++) {
		deret = [];
		for (j=0; j<jmlRekHome; j++) {
			//isi = (i*10+j);
			obj = {no: j, nama:"blavla", nilai:0, waktu:"0"};
			//obj = (i*10)+j;
			deret.push(obj);
			//document.getElementById('tahuIsi').innerHTML  += deret[j].nilai + " ";
		}
		arParam.push(deret);
	}
	//*/
}

function batalSetting() {
	masukSetting(0);
	/*alert("jmlRekHome");
	var jmlRekHome  = getCookie("jmlRekHome");
	var timeRefresh = getCookie("timeRefresh");
	alert(jmlRekHome);
	alert(timeRefresh);
	document.getElementById("jmlRekHome").innerHTML  = "jmlRekHome";
	//document.getElementById("timeRefresh").innerHTML = getCookies("timeRefresh");
	//*/
}

function paramSetting(nama, id, nilai, lokasi) {
	var tbl = document.getElementById(lokasi);
	var lastRow = tbl.rows.length;
	var isiTabel = tbl.insertRow(lastRow);
	
	var colSatu = isiTabel.insertCell(0);
	var colDua  = isiTabel.insertCell(1);
	colSatu.width     = 200;
	colSatu.vAlign    = "top";	
	colSatu.innerHTML = nama;	// 530 - 400 = 130
	
	//colDua.align 	  = "center"; 
	colDua.innerHTML  = ' : <input type=text id="' + id + '" size=41 value="' + nilai + '" title="' + nama + '" onfocus="setStyle(this.id)" onblur="unsetStyle(this.id)" >';
}

function masukHome() {
	// reset semua nilai awal;
	//arHome = [];
	var isi;
	var obj = {};
	var deret = [];
	for (i=0; i<jmlKW; i++) {
		deret = [];
		for (j=0; j<jmlRekHome; j++) {
			//isi = (i*10+j);
			obj = {no: j, nama:"blavla", nilai:0, waktu:"0"};
			//obj = (i*10)+j;
			deret.push(obj);
			//document.getElementById('tahuIsi').innerHTML  += deret[j].nilai + " ";
		}
		arHome.push(deret);
	}
	
	clearDetail();		//hapus semua record pada detail tiap parameter;
	
	/*
	for (i=0; i<jmlTitik; i++) {
		deret = [];
		for (j=0; j<jmlRekHome; j++) {
			//isi = (i*10+j);
			obj = {no: j, nama:"blavla", nilai:0, waktu:"0"};
			//obj = (i*10)+j;
			deret.push(obj);
			//document.getElementById('tahuIsi').innerHTML  += deret[j].nilai + " ";
		}
		arParam.push(deret);
	}
	//*/
	tahuIsiHome();
	
	var menuX = document.getElementById('menuEquip');
	menuX.innerHTML = "";
	//menuX.style.marginBottom = "0px";
	//menuX.style.marginTop = "0px";
	menuX.style.border = "0px solid #8E8E8E";
	menuX.style.padding = "0px";
	menuX.style.margin = "0px";
}

function clearDetail() {
	var deret = [];
	var obj = {};
	
	arParam = [];
	for (var i=0; i<jmlTitik; i++) {
		deret = [];
		for (var j=0; j<jmlRekHome; j++) {
			//isi = (i*10+j);
			obj = {no: j, nama:"blavla", nilai:0, waktu:"0"};
			//obj = (i*10)+j;
			deret.push(obj);
			//document.getElementById('tahuIsi').innerHTML  += deret[j].nilai + " ";
		}
		arParam.push(deret);
	}
}

function tahuIsiHome() {	// isi data pengukuran terbaru
	var str;
	stopTimer();
	if (isiHomeReq.readyState == 4 || isiHomeReq.readyState == 0) {
		str = "getData.php?fetchMenu=7";
		isiHomeReq.open("GET", str, true);
		isiHomeReq.onreadystatechange = handleReceiveDataHome; 
		isiHomeReq.send(null);
	}
}

function handleReceiveDataHome() {
	var tmpJudul = "";
	var total = 0;
	var jam, mnt, harga;
	var arData = [];
	var obj;
	
	if (isiHomeReq.readyState == 4) {
		var xmldoc = isiHomeReq.responseXML;
		var message_nodes = xmldoc.getElementsByTagName("item"); 
		var n_messages = message_nodes.length;
		jmlData = n_messages;
		if (n_messages > 0) {
			// bikin tabel
			document.getElementById('tahuIsi').innerHTML = '<div id="judulIsi"></div>';
			document.getElementById('tahuIsi').innerHTML += '<table id="tabelIsiTahu" border="1" bordercolor="black" cellpadding="14" cellspacing="0" width="530"><thead><tr align="center">' 
				+ '<th width="200"><b>Nama</b></th><th width="100"><b>Nilai (KW)</b></th><th><b>Update</b></th></tr></thead></table>';
			
			for (i = 0; i < n_messages; i++) {
				var nama   = message_nodes[i].getElementsByTagName("nama");
				var nilai  = message_nodes[i].getElementsByTagName("nilai");
				var titik  = message_nodes[i].getElementsByTagName("titik");
				var idwkt  = message_nodes[i].getElementsByTagName("idwkt");
				var waktu  = message_nodes[i].getElementsByTagName("waktu");
				var nEq    = message_nodes[i].getElementsByTagName("nEq");
				var kode   = message_nodes[i].getElementsByTagName("kode");
				var now    = message_nodes[i].getElementsByTagName("now");
				var nowMnt = (now[0].firstChild.nodeValue).substring(3,5);
				var nowJam = (now[0].firstChild.nodeValue).substring(0,2);
				dbJam  = (waktu[0].firstChild.nodeValue).substring(9,11);
				
				//if ( (parseInt((waktu[0].firstChild.nodeValue).substring(11,13))+tolMenit) > (parseInt(mnt)) )  
				{
					total += parseInt(nilai[0].firstChild.nodeValue);
					harga  = nilai[0].firstChild.nodeValue;
				//} else {
				//	harga = 0;
				}
				
				cssTahuIsiHome(nama[0].firstChild.nodeValue, harga, waktu[0].firstChild.nodeValue, 'tabelIsiTahu');
				//cssTahuIsiHome(nama[0].firstChild.nodeValue, nilai, waktu[0].firstChild.nodeValue);
				//cssTahuIsiHome(nowJam + " " + dbJam, harga, waktu[0].firstChild.nodeValue, 'tabelIsiTahu');
				obj = {no: i, nama: nama[0].firstChild.nodeValue, nilai: harga, waktu: waktu[0].firstChild.nodeValue};
				arData.push(obj);
			}
			cssTahuIsiHome("<b>Total Beban</b>", "<b>" + total + "</b>", "now", 'tabelIsiTahu');
			var judulIsi = '<h2 class="title"><strong>Beban Mesin</strong></h2>';
			document.getElementById('judulIsi').innerHTML = judulIsi.bold();
			document.getElementById('tahuIsi').innerHTML += "<br><br>";
			document.getElementById('tahuIsi').innerHTML += '<h2 class="title"><strong>Grafik Beban Mesin</strong></h2>';
			document.getElementById('tahuIsi').innerHTML += '<table id="tabelIsiGrafik" border="1" bordercolor="black" cellpadding="1" cellspacing="0" width="530"></table>';

			for (var i=0; i<n_messages; i++)
				cssTahuIsiGrafik(i, arData[i], "tabelIsiGrafik");
			/*
			cssTahuIsiGrafik(0, arData[0], "tabelIsiGrafik");
			cssTahuIsiGrafik(1, arData[1], "tabelIsiGrafik");
			cssTahuIsiGrafik(2, arData[2], "tabelIsiGrafik");
			cssTahuIsiGrafik(3, arData[3], "tabelIsiGrafik");
			cssTahuIsiGrafik(4, arData[4], "tabelIsiGrafik");
			//*/
		}                                       
		toH = setTimeout("tahuIsiHome(" + id_dept + "," + noAlat + ")",timeRefresh); //Refresh our chat in 2 seconds
	}
}

function cssTahuIsiHome(nama, nilai, waktu, lokasi) {
	var tbl = document.getElementById(lokasi);
	var lastRow = tbl.rows.length;
	var isiTabel = tbl.insertRow(lastRow);
	
	var colSatu = isiTabel.insertCell(0);
	var colDua  = isiTabel.insertCell(1);
	var colTiga = isiTabel.insertCell(2);
	
	colSatu.innerHTML = nama;
	if (nama = "<b>Total Beban</b>")
		colSatu.align = "center"; 
	colDua.align 	  = "center"; 
	colTiga.align 	  = "center"; 
	//	01/02/2008 19:43:34
	
	colTiga.innerHTML = formatWaktu(waktu);
	colDua.innerHTML  = nilai;
}	
//*/
function cssTahuIsiGrafik(no, data, lokasi) {
	var tbl = document.getElementById(lokasi);
	var lastRow = tbl.rows.length;
	var isiTabel = tbl.insertRow(lastRow);
	
	var colSatu = isiTabel.insertCell(0);
	var colDua  = isiTabel.insertCell(1);
	colSatu.width     = 400;
	colSatu.height    = 180;
	colSatu.vAlign    = "top";	
	colSatu.innerHTML = '<div id="mesin' + (no+1) + '" style="height:180px"></div>';	// 530 - 400 = 130

	colDua.align 	  = "center"; 
	colDua.innerHTML  = '<div id="ktrgn' + (no+1) + '" style="width:130px"></div>' + '<b>&nbsp;&nbsp;' + data.nama + "</b><br>" + data.nilai + " kW<br>" + formatWaktu(data.waktu);
	// data  = obj = {no: i, nama: nama[0].firstChild.nodeValue, nilai: harga, waktu: waktu[0].firstChild.nodeValue};
	fetchKW(no, data, "mesin" + (no+1), 6000, " ", 1, 10, 10);
}

function cssTahuIsiDetail(no, data, lokasi) {
	var tbl = document.getElementById(lokasi);
	var lastRow = tbl.rows.length;
	var isiTabel = tbl.insertRow(lastRow);
	
	var colSatu = isiTabel.insertCell(0);
	var colDua  = isiTabel.insertCell(1);
	colSatu.width     = 400;
	colSatu.height    = 180;
	colSatu.vAlign    = "top";
	colSatu.innerHTML = '<div id="param' + (no+1) + '" style="height:180px"></div>';	// 530 - 400 = 130

	colDua.align 	  = "center"; 
	colDua.innerHTML  = '<div id="ktrgn' + (no+1) + '" style="width:130px"></div>' + '<b>&nbsp;&nbsp;' + data.nama + "</b><br>" + desimal(data.nilai,AP) + " " + data.sat + "<br>" + formatWaktu(data.waktu);

	fetchParam(no, data, "param" + (no+1), 6000, " ", 1, 10, 10);
}

function tahuIsiMesin(dept, menu) {	// isi data pengukuran terbaru
	var str;
	id_dept = dept;
	noAlat = menu;
	stopTimer();
	noJdlTbl = 0;
	if (isiMesinReq.readyState == 4 || isiMesinReq.readyState == 0) {
		str = "getData.php?fetchMenu=6";
		str+= "&id_dept=" + dept;
		str+= "&id_menu=" + menu;
		//document.getElementById('footer').innerHTML = str;
		isiMesinReq.open("GET", str, true);
		isiMesinReq.onreadystatechange = handleReceiveDataMesin; 
		isiMesinReq.send(null);
	}
}

function handleReceiveDataMesin() {
	var tmpJudul = "";
	if (isiMesinReq.readyState == 4) {
		var xmldoc = isiMesinReq.responseXML;
		var message_nodes = xmldoc.getElementsByTagName("pesan"); 
		var n_messages = message_nodes.length;
		jmlData = n_messages;
		if (n_messages > 0) {
			// bikin tabel
			document.getElementById('tahuIsi').innerHTML = '<div id="judulIsi"></div>';
			//document.getElementById('tahuIsi').innerHTML += '<table id="tabelIsiTahu" border="1" width="500"><thead><tr align="center">' 
			//	+ '<th width="300"><b>Nama</b></th><th width="100"><b>Nilai</b></th><th><b>Satuan</b></th><th><b>Update</b></th></tr></thead></table>';
			document.getElementById('tahuIsi').innerHTML += '<table id="tabelIsiTahu" border="1" bordercolor="black" cellpadding="14" cellspacing="0" width="530"><thead><tr align="center">' 
				+ '<th width="200"><b>Nama</b></th><th width="100"><b>Nilai</b></th><th><b>Satuan</b></th><th><b>Update</b></th></tr></thead></table>';
			
			for (i = 0; i < n_messages; i++) {
				var nama   = message_nodes[i].getElementsByTagName("nama");
				var nilai  = message_nodes[i].getElementsByTagName("nilai");
				var titik  = message_nodes[i].getElementsByTagName("titik");
				var klp    = message_nodes[i].getElementsByTagName("klp");
				var sat    = message_nodes[i].getElementsByTagName("sat");
				var nEq    = message_nodes[i].getElementsByTagName("nEq");
				var nKlp   = message_nodes[i].getElementsByTagName("nKlp");
				var waktu  = message_nodes[i].getElementsByTagName("waktu");
				if (nKlp[0].firstChild.nodeValue != tmpJudul)  {					
					tmpJudul = nKlp[0].firstChild.nodeValue;
					tambahJudulTabel("tabelIsiTahu", tmpJudul);
				}
				cssTahuIsi(nama[0].firstChild.nodeValue, nilai[0].firstChild.nodeValue, sat[0].firstChild.nodeValue, waktu[0].firstChild.nodeValue);
				//cssTahuIsi(nama[0].firstChild.nodeValue, nilai[0].firstChild.nodeValue, sat[0].firstChild.nodeValue, waktu[0].firstChild.nodeValue);
			}
			var judulIsi = '<h2 class="title"><strong>Parameter ' + nEq[0].firstChild.nodeValue + '</strong></h2>';
			document.getElementById('judulIsi').innerHTML = judulIsi.bold();
		} 
		toM = setTimeout("tahuIsiMesin(" + id_dept + "," + noAlat + ")",timeRefresh); //Refresh our chat in 2 seconds
	}
}

function tambahJudulTabel(namaTabel, namaJudul) {
	var tbl = document.getElementById(namaTabel);
	var lastRow = tbl.rows.length;
	var isiTabel = tbl.insertRow(lastRow);
	satu = isiTabel.insertCell(0);
	noJdlTbl += 1;
	var idnya = "nKlp" + noJdlTbl;
	satu.id = idnya;
	//satu.background = "red";
	document.getElementById(idnya).colSpan = "4";
	satu.innerHTML = namaJudul.bold();
	
}
//*/

function tahuIsi(dept, menu, submenu) {	// isi data pengukuran terbaru
	var str;
	id_dept = dept;
	noAlat = menu;
	noSubAlat = submenu;
	stopTimer();
	//document.getElementById('tahuIsi').innerHTML = "Isi data : <br>";
	if (isiReq.readyState == 4 || isiReq.readyState == 0) {
		str = "getData.php?fetchMenu=5";
		str+= "&id_dept=" + dept;
		str+= "&id_menu=" + menu;
		str+= "&id_subm=" + submenu;
		//document.getElementById('footer').innerHTML = str;
		isiReq.open("GET", str, true);
		isiReq.onreadystatechange = handleReceiveDataPoint; 
		isiReq.send(null);
	}
}

function handleReceiveDataPoint() {
	var arData = [];
	var obj;
	
	if (isiReq.readyState == 4) {
		var xmldoc = isiReq.responseXML;
		var message_nodes = xmldoc.getElementsByTagName("pesan"); 
		var n_messages = message_nodes.length;
		//document.getElementById('jmlNode').value=n_messages;
		jmlData = n_messages;
		//document.getElementById('tahuIsi').innerHTML = 'testing isi ';
		if (n_messages > 0) {
			// bikin tabel
			document.getElementById('tahuIsi').innerHTML = '<div id="judulIsi"></div>';
			document.getElementById('tahuIsi').innerHTML += '<table id="tabelIsiTahu" border="1" bordercolor="black" cellpadding="14" cellspacing="0" width="530"><tr align="center">' 
				+ '<td width="200"><b>Nama</b></td><td width="100"><b>Nilai</b></td><td><b>Satuan</b></td><td><b>Update</b></td></tr></table>';
			//document.getElementById('tahuIsi').innerHTML = '';
			for (i = 0; i < n_messages; i++) {
				//document.getElementById('tahuIsi').innerHTML += '<td>nama </td>';
				var nama   = message_nodes[i].getElementsByTagName("nama");
				var nilai  = message_nodes[i].getElementsByTagName("nilai");
				var waktu  = message_nodes[i].getElementsByTagName("waktu");
				var titik  = message_nodes[i].getElementsByTagName("titik");
				var klp    = message_nodes[i].getElementsByTagName("klp");
				var sat    = message_nodes[i].getElementsByTagName("sat");
				var nEq    = message_nodes[i].getElementsByTagName("nEq");
				var nKlp   = message_nodes[i].getElementsByTagName("nKlp");

				cssTahuIsi(nama[0].firstChild.nodeValue, nilai[0].firstChild.nodeValue, sat[0].firstChild.nodeValue, waktu[0].firstChild.nodeValue);
				obj = {no: i, nama: nama[0].firstChild.nodeValue, nilai: nilai[0].firstChild.nodeValue, sat: sat[0].firstChild.nodeValue, waktu: waktu[0].firstChild.nodeValue};
				arData.push(obj);
			}
			
			var judulIsi = '<h2 class="title"><strong>Parameter ' + nKlp[0].firstChild.nodeValue + ' pada ' + nEq[0].firstChild.nodeValue + '</strong></h2>';
			document.getElementById('judulIsi').innerHTML = judulIsi.bold();

			document.getElementById('tahuIsi').innerHTML += "<br><br>";
			document.getElementById('tahuIsi').innerHTML += '<h2 class="title"><strong>Grafik Parameter Detail Mesin</strong></h2>';
			document.getElementById('tahuIsi').innerHTML += '<table id="tabelIsiGrafik" border="1" bordercolor="black" cellpadding="1" cellspacing="0" width="530"></table>';
			
			//alert("nongol" + n_messages);
			
			for (var i=0; i<n_messages; i++) {
				//alert("nongol " + (i));
				cssTahuIsiDetail(i, arData[i], "tabelIsiGrafik");
			}			
		} //else {
		//	
		//}
		//if (status == 1) {
			toI = setTimeout("tahuIsi(" + id_dept + "," + noAlat + "," + noSubAlat + ")",timeRefresh); //Refresh our chat in 2 seconds
		//}
		//status = 1;
		//setTimeout(tahuIsi(1, 2, 6),2000); //Refresh our chat in 2 seconds
	}
}

function cssTahuIsi(idnama, idnilai, idtitik, waktu) {
//	insRow();
	var tbl = document.getElementById('tabelIsiTahu');
	var lastRow = tbl.rows.length;
	var isiTabel = tbl.insertRow(lastRow);
	//var tblIsi  = tbl.insertRow(1);
	var colSatu  = isiTabel.insertCell(0);
	var colDua   = isiTabel.insertCell(1);
	var colTiga  = isiTabel.insertCell(2);
	var colEmpat = isiTabel.insertCell(3);
	
	//colSatu.height     = 200;
	colSatu.innerHTML  = idnama;
	colDua.innerHTML   = desimal(idnilai,AP);
	//colDua.innerHTML   = idnilai.toFixed(AP);
	colDua.align 	   = "center"; 
	colTiga.innerHTML  = idtitik;
	colTiga.align 	   = "center"; 
	colEmpat.innerHTML = formatWaktu(waktu);
	colEmpat.align 	   = "center"; 
}

/*
function tambahTabel(nilai) {
	var x = parseInt((nilai+1)/2);
	for (i=x; i>0; i--) {
		var isiTabel = document.getElementById("tblGrafik").insertRow(1);
		var satu = isiTabel.insertCell(0);
		var dua  = isiTabel.insertCell(1);
		satu.innerHTML = '<table border="0"><tr><td><div id="waktu' + ((i*2)-1) + '">waktu' + ((i*2)-1) + '</div></td><td><div id="nilai' + ((i*2)-1) + '">nilai' + ((i*2)-1) + '</div></td><td><div id="satuan' + ((i*2)-1) + '">satuan' + ((i*2)-1) + '</div></td></tr></table>';
		dua.innerHTML  = '<table border="0"><tr><td><div id="waktu' + (i*2) + '">waktu' + (i*2) + '</div></td><td><div id="nilai' + (i*2) + '">nilai' + (i*2) + '</div></td><td><div id="satuan' + (i*2) + '">satuan' + (i*2) + '</div></td></tr></table>';
		
		isiTabel = document.getElementById("tblGrafik").insertRow(1);
		satu = isiTabel.insertCell(0);
		dua  = isiTabel.insertCell(1);
		satu.innerHTML = '<div id="grafik' + ((i*2)-1) + '">grafik' + ((i*2)-1) + '</div>';
		dua.innerHTML  = '<div id="grafik' + i*2 + '">grafik' + i*2 + '</div>';
		
		isiTabel = document.getElementById("tblGrafik").insertRow(1);
		satu = isiTabel.insertCell(0);
		dua  = isiTabel.insertCell(1);
		satu.innerHTML = '<div id="nama' + ((i*2)-1) + '">nama' + ((i*2)-1) + '</div>';
		dua.innerHTML  = '<div id="nama' + i*2 + '">nama' + i*2 + '</div>';
	}
}
*/

function desimal(nilai,angkapenting) {
	var hasil;
	if (nilai.indexOf('.')>0) {
		return (nilai.substring(nilai.indexOf('.')+angkapenting+1,0));
		//return nilai.toFixed(angkapenting);
	} else
		return nilai;
}

function stopTimer() {
	clearTimeout(toI);
	clearTimeout(toM);
	clearTimeout(toH);
}

function formatWaktu(data) {	// misal : 	20080124-164049
	if (data.length < 10) {
		return now();
	} else if (data.length < 16) {
		var tgl = data.substring(6,8);
		var bln = data.substring(4,6);
		var thn = data.substring(0,4);
	
		var jam = data.substring(9,11);
		var mnt = data.substring(11,13);
		var dtk = data.substring(13,15);
	
		return (tgl + "/" + bln + "/" + thn + " " + jam + ":" + mnt + ":" + dtk);
	} else {		
		return now();
	}
}

function now() {
	var t   = new Date();
	var tgl = t.getDate();
	var bln = t.getMonth() + 1;		// januari = 0
	var thn = t.getFullYear();
	var jam = t.getHours();
	var mnt = t.getMinutes();
	var dtk = t.getSeconds();
	
	return (t0(tgl) + "/" + t0(bln) + "/" + thn + " " + t0(jam) + ":" + t0(mnt) + ":" + t0(dtk));
}

function t0(data) {		// tambahkan nol di depan format waktu jika hanya 1 digit
	if (data < 10) {
		return ("0" + data);
	} else {
		return data;
	}
}



function dataHistori() {
	var id, tgl, awal, akhir;
	var str;	
	
	stopTimer();
	
	var x = document.getElementById("pilihHistori");
	id = x.options[x.selectedIndex].value;
	//*
	x = document.getElementById("jamAwal");
	awal = x.options[x.selectedIndex].value;	

	x = document.getElementById("jamAkhir");
	akhir = x.options[x.selectedIndex].value;	

	x = dojo.widget.byId("tanggalX");
	tgl = x.getValue();
	//*/
	
	//var as = "nilai = " + id + " tgl : " + tgl + " awal : " + awal + " akhir : " + akhir;
	//alert(as);
	
	if (id == 9999) {
		alert("Pilih titik ukur yang tepat");
		return 0;
	}
	var eTgl = tgl.substring(0,4) + "" + tgl.substring(5,7) + "" + tgl.substring(8,10);
	var tawal = eTgl + "-" + awal;
	var takhr = eTgl + "-" + akhir;
	
	//document.getElementById('tahuIsi').innerHTML = "<br><br>sedang mencari ... <br>";
	
	if (historiReq.readyState == 4 || historiReq.readyState == 0) {
		str = "getData.php?fetchMenu=8";
		str+= "&titik=" + id;
		str+= "&tawal=" + tawal;
		str+= "&takhr=" + takhr;
		historiReq.open("GET", str, true);
		historiReq.onreadystatechange = handleReceiveDataHistori; 
		historiReq.send(null);
		document.getElementById('tahuIsi').innerHTML = "<br><br>sedang mencari ... <br>";
	}
	//*/
}

function handleReceiveDataHistori() {
	arHistori = [];
	var obj = {};
	if (historiReq.readyState == 4) {
		var xmldoc = historiReq.responseXML;
		var message_nodes = xmldoc.getElementsByTagName("pesan"); 
		var n_messages = message_nodes.length;
		jmlData = n_messages;
		var nama, mesin;
		
		if (n_messages > 0) {
			// bikin tabel
			document.getElementById('tahuIsi').innerHTML  = '<div id="judulIsi"></div>';
			document.getElementById('tahuIsi').innerHTML += '<div id="wadahHistori" style="height:200px";></div>';
			document.getElementById('tahuIsi').innerHTML += '<table id="tabelIsiTahu" border="1" bordercolor="black" cellpadding="14" cellspacing="0" width="500"><tr align="center">' 
				+ '<td width="50"><b>No</b></td><td width="150"><b>Nilai</b></td><td><b>Waktu</b></td></tr></table>';
	
			for (i = 0; i < n_messages; i++) {
				var data    = message_nodes[i].getElementsByTagName("data");
				var waktu   = message_nodes[i].getElementsByTagName("waktu");
				nama        = message_nodes[i].getElementsByTagName("nama");
				mesin       = message_nodes[i].getElementsByTagName("mesin");
				var fwaktu  = formatWaktu(waktu[0].firstChild.nodeValue);
				cssTahuIsiHistori(i+1, data[0].firstChild.nodeValue, fwaktu);	
				obj = {no: (i+1), nilai: data[0].firstChild.nodeValue, time: fwaktu};
				arHistori.push(obj);
			}
			var judulIsi = "Histori <b>" + nama[0].firstChild.nodeValue + "</b> pada <b>" + mesin[0].firstChild.nodeValue + "</b> ditemukan <b>" + jmlData + "</b> data ";
			//judulIsi += '    <input type=BUTTON value="Print" onClick="window.print()">';
			
			document.getElementById('judulIsi').innerHTML = judulIsi;
			document.getElementById('tahuIsi').innerHTML += "<br><br>";
			
			//document.getElementById('judulIsi').innerHTML = judulIsi;
			//initGrafik(1);
			arHistori.reverse();
			//document.getElementById('tahuIsi').innerHTML += arHistori.reverse();
			//document.getElementById('tahuIsi').innerHTML += "<br>" + arHistori[0].nilai;
			//document.getElementById('tahuIsi').innerHTML += "<br>" + arHistori.length;
			
			var max = maxNilai(arHistori) * 1.05;
			var min = minNilai(arHistori) - (0.05 * abs(minNilai(arHistori)) );	// -3  - mutlak(nilai)  = -3.3
			var nm  = nama[0].firstChild.nodeValue + "   " + mesin[0].firstChild.nodeValue;
			//alert("max nilai : " + max);
			
			fetch(arHistori, "wadahHistori", max, min, nm, 10, 20, 20);
			//fetch(nilai, GraphArea, hmax, labelY, periode, posX, posY)
		} else {
			document.getElementById('tahuIsi').innerHTML = "<br><br>Data tidak ditemukan. ";
		}
	}	
}

function maxNilai(data) {
	var tmpA = Number.MIN_VALUE, idx = 0;
	for (i=0; i<data.length; i++) {
		if (tmpA < parseFloat(data[i].nilai)) {
			tmpA = data[i].nilai;
			idx = i;
		}
	}
	var sss = "jml data : " + data.length + ", max : " + tmpA + ", idx : " + (data.length-idx);
	//sss += data[0].nilai + " " + data[1].nilai + " " + data[2].nilai + " " + data[3].nilai + " " + data[4].nilai + " ";
	//alert(sss);
	return tmpA;
}

function minNilai(data) {
	var tmpA = Number.MAX_VALUE, idx = 0;
	for (i=0; i<data.length; i++) {
		if (tmpA > parseFloat(data[i].nilai)) {
			tmpA = data[i].nilai;
			idx = i;
		}
	}
	var sss = "jml data : " + data.length + ", max : " + tmpA + ", idx : " + (data.length-idx) + ", abs : " + abs(tmpA);
	//sss += data[0].nilai + " " + data[1].nilai + " " + data[2].nilai + " " + data[3].nilai + " " + data[4].nilai + " ";
	//alert(sss);
	return tmpA;
}

function abs(data) {
	if (data>=0)
		return data;
	else
		return (-data);
}

function cssTahuIsiHistori(idnama, idnilai, idtitik) {
//	insRow();
	var tbl = document.getElementById('tabelIsiTahu');
	var lastRow = tbl.rows.length;
	var isiTabel = tbl.insertRow(lastRow);
	//var tblIsi  = tbl.insertRow(1);
	var colSatu  = isiTabel.insertCell(0);
	var colDua   = isiTabel.insertCell(1);
	var colTiga  = isiTabel.insertCell(2);

	colSatu.align 	   = "center"; 
	colSatu.innerHTML  = idnama;
	colDua.innerHTML   = desimal(idnilai,AP);
	colDua.align 	   = "center"; 
	colTiga.innerHTML  = idtitik;
	colTiga.align 	   = "center"; 
}
//*
function compare(a, b) {
   // psudeo code.
   if (a < b) {
      return -1;
   }
   if (a > b) {
      return 1;
   }
   if (a == b) {
      return 0;
   }
}
//*/
function fetch(nilai, GraphArea, hmax, hmin, labelY, periode, posX, posY) {
	//var d = [1000,4000,7600,8700,3000,600,230,1000,4000,7600,8700,3000,600,230,1000,4000,7600,8700,3000,600,230,1000,4000,7600,8700,3000,600,230,6200,0,50,700,2000,60,90, 1000,10000,60,90, 1000,10000];
	
	var d = [];
	for (i=0; i<(arHistori.length); i++) {
		d.push(arHistori[i].nilai);
	}
	//document.getElementById('tahuIsi').innerHTML += d + "<br>";
	//var e = [];
	//e = d;
	//e.sort(compare);
	//e.sort(function (a,b) { return a-b })
	
	var obj = {};
	var exampleData  = [];
	
	for (i=0; i<d.length; i++) {
		obj = { no: i, y: arHistori[i], x: "x"+i };
		exampleData.push(obj);
	}
	
	grafik(exampleData, GraphArea, hmax, hmin, labelY, periode, posX, posY);
}


function grafik(dataChart, lokasi, hmax, hmin, labelY, periode, posX, posY) {
	var obj;
	var bwh = hmin;
	//alert(hmin);
	var jmlY = 5;
	var period = 15;
	//var labelX = [];
	//for (i=0; i<(dataChart.length/2); i+=2) {
	//	labelX[i] = (periode + i*periode);
	//}
	
	if (arHistori.length < period)
		period = arHistori.length;
	
	var store = new dojo.collections.Store();
	store.setData(arHistori);

	var timeSeries = new dojo.charting.Series({
		dataSource: store, bindings: { x: "no", y: "nilai" }, label: "Example Series"
	}); 
	
	//Define the x-axis
	var xAxis = new dojo.charting.Axis();

	//Set the upper and lower data range values
	xAxis.range = { lower: arHistori[0].no, upper: arHistori[arHistori.length-1].no	 };

	xAxis.origin = "max";
	xAxis.showLines = true;
	xAxis.showTicks = true;
	xAxis.label = "nomor waktu";

	//Setup the x tick marks on the chart
	/*
	xAxis.labels = [
		{ label: labelX[9], value: 0 },
		{ label: labelX[8], value: 1 },
		{ label: labelX[7], value: 2 },
		{ label: labelX[6], value: 3 },
		{ label: labelX[5], value: 4 },
		{ label: labelX[4], value: 5 },
		{ label: labelX[3], value: 6 },
		{ label: labelX[2], value: 7 },
		{ label: labelX[1], value: 8 },
		{ label: labelX[0], value: 9 },
		{ label: 'Now', value: 10 },
	];
	//*/
	var lblX = {};
	
	var delay = parseInt(arHistori.length/period);
	
	
	for (j=0; j<(arHistori.length); j+=delay) {
	//for (j=0; j<(arHistori.length); j++) {
		lbl = {label: (arHistori[j].no), value: arHistori[j].no};
		(xAxis.labels).push(lbl);	
	}
	//lbl = {label: "now", value: (arHistori.length-1)};
	//(xAxis.labels).push(lbl);	
	
	//Define the y-axis
	var yAxis = new dojo.charting.Axis();
	yAxis.range = { lower: bwh, upper: hmax };
	yAxis.showLines = true;
	yAxis.showTicks = true;
	//yAxis.label = labelY;
	yAxis.label = "";

	//Setup the y tick marks on the chart
	/*
	yAxis.labels = [
		{ label: "0", value: 000 },
		{ label: "2000", value: 2000 },
		{ label: "4000", value: 4000 },
		{ label: "6000", value: 6000 },
		{ label: "8000", value: 8000 },
		{ label: "10000", value: 10000 }
	];
	//*/
	var lblY = [];
	var gridYy;	// jarak antar nilai Y.
	
	var grid = (hmax-bwh)/jmlY;
	for(var k=0; k<=(jmlY); k++) {
		//gridYy = (k*grid+bwh).toPrecision(5);
		gridYy = (k*grid+bwh).toString();
		if (gridYy > 200000) // jika selang Y > 200000, untuk kWh yang kepotong nilai ujungnya, 1234567 menjadi 234567
			gridYy = desimal(gridYy,0);
		else
			gridYy = desimal(gridYy,2);

		obj = { label: gridYy, value: (k*grid+bwh) };
		//obj = {label: (k*grid+bwh), value: (k*grid)+bwh};
		(yAxis.labels).push(obj);
	}
	//document.getElementById('tahuIsi').innerHTML += (yAxis.labels)[3].value + "<br>";
	
	var chartPlot = new dojo.charting.Plot(xAxis, yAxis);

	chartPlot.addSeries({
		data: timeSeries, plotter: dojo.charting.Plotters.CurvedArea
	}); 

	var chartPlotArea = new dojo.charting.PlotArea();
	chartPlotArea.size = { width: 470, height: 170 };
	chartPlotArea.padding = { top: 20, right: 20, bottom: 30, left: 50 };

	timeSeries.color = chartPlotArea.nextColor();

	//Add the plot to the area
	chartPlotArea.plots.push(chartPlot); 

	//var chart = new dojo.charting.Chart(null, "Example chart", "This is the example chart description");
	var chart = new dojo.charting.Chart(null, "Example chart", "This is the example chart description");
	
	//Add the plot area at an offset of 10 pixels from the top left
	chart.addPlotArea({ x: posX, y: posY, plotArea: chartPlotArea });	

	chart.node = dojo.byId(lokasi);
	chart.render();
	
	store = null;
	timeSeries = null;
	xAxis = null;
	yAxis = null;
	chartPlot = null;
	chartPlotArea = null;
	chart = null;
}


function isiPilihHistori() {
	var str;
	stopTimer();
	
	var t   = new Date();
	var jam = t.getHours();
	var mnt = t.getMinutes();
	var dtk = t.getSeconds();
	
	opsiHistori(t0(jam)+":"+t0(mnt), t0(jam) +""+ t0(mnt), "jamAkhir");
	for (i=0; i<24; i++) {
		if (i < 10) 
			jam = "0" + i;
		else
			jam = i;
		opsiHistori(jam + ":00", jam+"00", "jamAwal");
		opsiHistori(jam + ":59", jam+"59", "jamAkhir");
	}
	if (opsiHistoriReq.readyState == 4 || opsiHistoriReq.readyState == 0) {
		str = "getData.php?fetchMenu=9";
		opsiHistoriReq.open("GET", str, true);
		opsiHistoriReq.onreadystatechange = handleReceiveOpsiHistori; 
		opsiHistoriReq.send(null);
	}
}

function handleReceiveOpsiHistori() {
	var tmpNilai = " ";
	if (opsiHistoriReq.readyState == 4) {
		var xmldoc = opsiHistoriReq.responseXML;
		var message_nodes = xmldoc.getElementsByTagName("pesan"); 
		var n_messages = message_nodes.length;
		jmlData = n_messages;
		/*
		if (n_messages > 0) {
			opsiHistori(" -- Pilih -- ", 99, "pilihHistori");
			for (i = 0; i < n_messages; i++) {
				var nama   = message_nodes[i].getElementsByTagName("nama");
				var titik  = message_nodes[i].getElementsByTagName("titik");
				var klp    = message_nodes[i].getElementsByTagName("klp");
				var mesin  = message_nodes[i].getElementsByTagName("mesin");
				
				if  (tmpNilai != klp[0].firstChild.nodeValue) {
					opsiHistori(klp[0].firstChild.nodeValue + " " + mesin[0].firstChild.nodeValue, 99, "pilihHistori");
					tmpNilai = klp[0].firstChild.nodeValue;
				}
				opsiHistori(nama[0].firstChild.nodeValue, titik[0].firstChild.nodeValue, "pilihHistori");
			}
		} //else {
		*/
		var tmpG = " ";
		var tmpM = " ";
		var flagM = 0;
		var flagG = 0;
		
		//var x = "jml data : " + n_messages;
		//alert(x);
		
		if (n_messages > 0) {
			opsiTitikHistori("-- Pilih Titik -- ", " ", " ", 9999, 0, 0, "pilihHistori");
			for (i = 0; i < n_messages; i++) {
				var nama   = message_nodes[i].getElementsByTagName("nama");
				var titik  = message_nodes[i].getElementsByTagName("titik");
				var grup   = message_nodes[i].getElementsByTagName("grup");
				var mesin  = message_nodes[i].getElementsByTagName("mesin");
				
				var isiG   = grup[0].firstChild.nodeValue;
				var isiM   = mesin[0].firstChild.nodeValue;
				var isiN   = nama[0].firstChild.nodeValue;
				var isiT   = titik[0].firstChild.nodeValue;
				
				if (tmpG != isiG) {	// jika tidak sama
					flagG = 1;
					tmpG = isiG;
				} else {
					flagG = 0;
				}	
				
				if (tmpM != isiM) {	// jika tidak sama
					flagM = 1;
					tmpM = isiM;
				} else {
					flagM = 0;
				}
				
				opsiTitikHistori(isiN, isiG, isiM, isiT, flagG, flagM, "pilihHistori");
			}
		} 
	}
}

function opsiTitikHistori(nama, grup, mesin, titik, flagG, flagM, elemen) {
	
	var x   = document.getElementById(elemen);
	
	if (flagM) {
		//var msn	= document.createElement('optgroup');
		//msn.label = " ";
		//x.appendChild(msn);
		var msn	= document.createElement('optgroup');
		msn.label = "== " + mesin + " ==";
		x.appendChild(msn);
	}
	
	if (flagG) {
		var z	= document.createElement('optgroup');
		z.label = grup;
		x.appendChild(z);
	}
	
	var y   = document.createElement('option');
	y.value = titik;
	y.text = nama;

	try {
		x.add(y,null); // standards compliant
	} catch(ex) {
		x.add(y); // IE only
	}
}


function opsiHistori(nama, titik, elemen) {
	var y   = document.createElement('option');
	y.value = titik;
	y.text  = nama;
	
	if (titik == "2359")
		y.selected = true;
	
	//y.width = 500;
	var x   = document.getElementById(elemen);
	try {
		x.add(y,null); // standards compliant
	} catch(ex) {
		x.add(y); // IE only
	}
}

function fetchKW(no, data, GraphArea, hmax, labelY, periode, posX, posY) {
	arHome[no].shift();
	arHome[no].push(data);
	
	for (i=0; i<arHome[no].length; i++) {
		arHome[no][i].no = i;
	}
	
	var exampleData = arHome[no];
	//for (i=0; i<exampleData[1]; i++) {
		//document.getElementById('identitas').innerHTML += exampleData[0].nilai + " " + exampleData[1].nilai + " " + exampleData[2].nilai + " " + exampleData[3].nilai + " " + exampleData[4].nilai;
		//document.getElementById('identitas').innerHTML += exampleData[0].no + " " + exampleData[1].no + " " + exampleData[2].no + " " + exampleData[3].no + " " + exampleData[4].no;
		//document.getElementById('identitas').innerHTML += arHome[0][0].nilai + " " + arHome[0][1].nilai + " " + arHome[0][2].nilai + " " + arHome[0][3].nilai + " " + arHome[0][4].nilai +  + data.nilai;
		//document.getElementById('identitas').innerHTML += "<br>";
	//}
	grafikKW(exampleData, GraphArea, hmax, labelY, periode, posX, posY);
}

function fetchParam(no, data, GraphArea, hmax, labelY, periode, posX, posY) {
	arParam[no].shift();
	arParam[no].push(data);

	for (i=0; i<arParam[no].length; i++) {
		arParam[no][i].no = i;
	}

	var exampleData = arParam[no];
	//for (i=0; i<exampleData[1]; i++) {
		//document.getElementById('identitas').innerHTML += exampleData[0].nilai + " " + exampleData[1].nilai + " " + exampleData[2].nilai + " " + exampleData[3].nilai + " " + exampleData[4].nilai;
		//document.getElementById('identitas').innerHTML += exampleData[0].no + " " + exampleData[1].no + " " + exampleData[2].no + " " + exampleData[3].no + " " + exampleData[4].no;
		//document.getElementById('identitas').innerHTML += arHome[0][0].nilai + " " + arHome[0][1].nilai + " " + arHome[0][2].nilai + " " + arHome[0][3].nilai + " " + arHome[0][4].nilai +  + data.nilai;
		//document.getElementById('identitas').innerHTML += "<br>";
	//}
	
	var max = maxNilai(arParam[no]) * 1.05;
	var min = minNilai(arParam[no]) - (0.05 * abs(minNilai(arParam[no])) );	// -3  - mutlak(nilai)  = -3.3
	
	grafikParam(exampleData, GraphArea, (max+1), min, labelY, periode, posX, posY);
}

function grafikParam(dataChart, lokasi, hmax, hmin, labelY, periode, posX, posY) {
	var bwh = hmin;
	var tinggi = 6;
	
	var store = new dojo.collections.Store();
	store.setData(dataChart);

	var timeSeries = new dojo.charting.Series({
	dataSource: store,
	bindings: { x: "no", y: "nilai" },
	label: "Example Series"
	}); 

	//Define the x-axis
	var xAxis = new dojo.charting.Axis();

	//Set the upper and lower data range values
	xAxis.range = { lower: dataChart[0].no, upper: dataChart[dataChart.length-1].no };

	xAxis.origin = "max";
	xAxis.showTicks = true;
	xAxis.showLines = true;
	xAxis.label = "waktu";

	//Setup the x tick marks on the chart
	//*
	var lblX = {};	
	for (j=(dataChart.length); j>1; j--) {
		lbl = {label: j-1, value: (dataChart.length-j)};
		(xAxis.labels).push(lbl);	
	}
	lbl = {label: "now", value: (dataChart.length-1)};
	(xAxis.labels).push(lbl);
	//*/
	
	//Define the y-axis
	var yAxis = new dojo.charting.Axis();
	yAxis.range = { lower: bwh, upper: hmax };
	yAxis.showLines = true;
	yAxis.showTicks = true;
	//yAxis.label = "Time Taken";

	//Setup the y tick marks on the chart
	var grid = (hmax-bwh)/tinggi;
	var lblY = [];
	var gridYy;
	
	for(var k=0; k<=tinggi; k++) {
		gridYy = (k*grid+bwh).toString();
		if (gridYy > 200000)
			gridYy = desimal(gridYy, 0);
		else
			gridYy = desimal(gridYy, 2);
		
		obj = { label: gridYy, value: (k*grid+bwh) };
		//obj = {label: (k*grid+bwh).toString(), value: (k*grid)+bwh};
		(yAxis.labels).push(obj);
	}
	
	var chartPlot = new dojo.charting.Plot(xAxis, yAxis);

	chartPlot.addSeries({
		data: timeSeries, plotter: dojo.charting.Plotters.CurvedArea
	}); 

	var chartPlotArea = new dojo.charting.PlotArea();
	//chartPlotArea.size = { width: 370, height: 170 };
	//chartPlotArea.padding = { top: 20, right: 20, bottom: 30, left: 50 };
	
	chartPlotArea.size = { width: 380, height: 170 };
	chartPlotArea.padding = { top: 20, right: 20, bottom: 35, left: 40 };
	
	//Add the plot to the area
	chartPlotArea.plots.push(chartPlot); 
	timeSeries.color = chartPlotArea.nextColor();	
	
	var chart = new dojo.charting.Chart(null, "Example chart", "This is the example chart description");

	//Add the plot area at an offset of 10 pixels from the top left
	chart.addPlotArea({ x: posX, y: posY, plotArea: chartPlotArea });

	chart.node = dojo.byId(lokasi);
	chart.render();

	store = null;
	timeSeries = null;
	xAxis = null;
	yAxis = null;
	chartPlot = null;
	chartPlotArea = null;
	chart = null;
}

function grafikKW(dataChart, lokasi, hmax, labelY, periode, posX, posY) {
	var bwh = 0;
	var tinggi = 6;
	
	var store = new dojo.collections.Store();
	store.setData(dataChart);

	var timeSeries = new dojo.charting.Series({
	dataSource: store,
	bindings: { x: "no", y: "nilai" },
	label: "Example Series"
	}); 


	//Define the x-axis
	var xAxis = new dojo.charting.Axis();

	//Set the upper and lower data range values
	xAxis.range = { lower: dataChart[0].no, upper: dataChart[dataChart.length-1].no };

	xAxis.origin = "max";
	xAxis.showTicks = true;
	xAxis.showLines = true;
	xAxis.label = "waktu";

	//Setup the x tick marks on the chart
	//*
	var lblX = {};	
	for (j=(dataChart.length); j>1; j--) {
		lbl = {label: j-1, value: (dataChart.length-j)};
		(xAxis.labels).push(lbl);	
	}
	lbl = {label: "now", value: (dataChart.length-1)};
	(xAxis.labels).push(lbl);
	//*/
	
	//Define the y-axis
	var yAxis = new dojo.charting.Axis();
	yAxis.range = { lower: bwh, upper: hmax };
	yAxis.showLines = true;
	yAxis.showTicks = true;
	//yAxis.label = "Time Taken";

	//Setup the y tick marks on the chart
	var grid = (hmax-bwh)/tinggi;
	for(k=0; k<=tinggi; k++) {
		obj = {label: (k*grid+bwh).toString(), value: (k*grid)+bwh};
		(yAxis.labels).push(obj);
	}
	
	var chartPlot = new dojo.charting.Plot(xAxis, yAxis);

	chartPlot.addSeries({
		data: timeSeries, plotter: dojo.charting.Plotters.CurvedArea
	}); 

	var chartPlotArea = new dojo.charting.PlotArea();
	//chartPlotArea.size = { width: 370, height: 170 };
	//chartPlotArea.padding = { top: 20, right: 20, bottom: 30, left: 50 };
	
	chartPlotArea.size = { width: 380, height: 170 };
	chartPlotArea.padding = { top: 20, right: 20, bottom: 35, left: 40 };
	
	//Add the plot to the area
	chartPlotArea.plots.push(chartPlot); 
	timeSeries.color = chartPlotArea.nextColor();	
	
	var chart = new dojo.charting.Chart(null, "Example chart", "This is the example chart description");

	//Add the plot area at an offset of 10 pixels from the top left
	chart.addPlotArea({ x: posX, y: posY, plotArea: chartPlotArea });

	chart.node = dojo.byId(lokasi);
	chart.render();

	store = null;
	timeSeries = null;
	xAxis = null;
	yAxis = null;
	chartPlot = null;
	chartPlotArea = null;
	chart = null;
}

function masukLogin() {
	var usr = document.getElementById("usr");
	var pwd = document.getElementById("pwd");
	var log = document.getElementById("btnLogin");

	//document.getElementById("tahuIsi").innerHTML = usr.value + " " + pwd.value;
	if (usr.value == "operator" && pwd.value == "opr" && log.value == "   Masuk   ") {
		masuk = 1;
		awalProses();
		document.getElementById("usr").value = "";
		document.getElementById("pwd").value = "";
		document.getElementById("btnLogin").value = "   Keluar   ";
	} else {//(log.value == "   Keluar   ") {
		masuk = 0;
		document.getElementById("btnLogin").value = "   Masuk   ";
		
		//document.getElementById('menuatas').innerHTML = "";
		document.getElementById('menuatas').innerHTML = menuHomeSaja();
		//masukHome();
		awalProses();
	}	
}

function pilihPLTD() {
	dojo.html.hide('spyPLTD');
	//var tutup = new dojo.widget.FloatingPane();
	//tutup.closeWindow();
	//alert("oke deh kakak");
}

function setStyle(x){
	document.getElementById(x).style.background="yellow";
}

function unsetStyle(x) {
	document.getElementById(x).style.background="white";
}

function getCookie(c_name) {
	if (document.cookie.length>0) {
		c_start=document.cookie.indexOf(c_name + "=");
		if (c_start != -1) {
			c_start = c_start + c_name.length+1;
			c_end = document.cookie.indexOf(";",c_start);
			if (c_end == -1) c_end=document.cookie.length;
			return unescape(document.cookie.substring(c_start,c_end));
		}
	}
	return "";
}

function setCookie(c_name,value,expiredays) {
	var exdate = new Date();
	exdate.setDate(exdate.getDate()+expiredays);
	document.cookie = c_name + "=" +escape(value)+((expiredays==null) ? "" : "; expires="+exdate.toGMTString());
}

function setCookiesDefault() {
	setCookie('jmlRekHome', jmlRekHome, tlCookies);
	setCookie('jmlTitik', jmlTitik, tlCookies);
	setCookie('timeRefresh', timeRefresh, tlCookies);
	setCookie('id_dept', id_dept, tlCookies);
	setCookie('usr', "operator", 1);
	setCookie('pwd', "opr", 1);
	
/*
	var d = new Date();
	var tgl = d.getDate() + " " + d.getMonth() + " " + d.getFullYear();
	alert(tgl);
	//exdate.setDate(exdate.getDate());
	setCookie('last_login', tgl, 1);
//*/
}

function cekCookies() {
	//stopTimer();
	//masukCek();
	var last_login = getCookie('last_login');
	if (last_login!=null && last_login!="") {
		jmlRekHome  = getCookie('jmlRekHome');
		timeRefresh = getCookie('timeRefresh');
		var xlastLogin = getCookie('last_login');
		var setting = document.getElementById('lastlogin');
		setting.innerHTML = "Login terakhir : " + xlastLogin;
		setting = document.getElementById('lastlogin');
		setting.innerHTML = "Login terakhir : " + xlastLogin;
		//alert("last Login : " + xlastLogin);
	} else {
		setCookiesDefault();
	}
	
	var d = new Date();
	var tgl = d.getDate() + " " + bulan[d.getMonth()] + " " + d.getFullYear();
	//alert(tgl);
	//exdate.setDate(exdate.getDate());
	setCookie('last_login', tgl, 1);
	
}

/*
function getCookiesDefault() {
	setCookie('jmlRekHome', 21, 1);
	setCookie('jmlTitik', 13, 1);
	setCookie('timeRefresh', 5000, 1);
	setCookie('id_dept', 3, 1);
}
//*/

function thnBawah() {
	var d = new Date();
	return d.getFullYear();
}
