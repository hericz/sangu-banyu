
// include buat grafik
dojo.require("dojo.collections.Store");
dojo.require("dojo.charting.Chart");

var AP = 3;		// jml angka penting dalam desimal

//function startup() {
//	//fetchKWz();
//}

function nilaiAwal(jmlArr) {
	for(var i=0; i<jmlArr; i++) {
		
	}
}

function fetchKWz() {
	var exampleData = [];
	var obj = {};
	for (j=0; j<11; j++) {
		isi = (10+j*5);
		obj = {no: j, nama:"blavla", nilai:isi, waktu:"0"};
		exampleData.push(obj);
	}
	document.getElementById('tahuIsi').innerHTML  = exampleData[0].nilai + " " + exampleData[1].nilai + " " + exampleData[2].nilai + " " + exampleData[3].nilai + " " + exampleData[4].nilai + " " + exampleData[5].nilai + "<br>";
	document.getElementById('tahuIsi').innerHTML += exampleData[0].no + " " + exampleData[1].no + " " + exampleData[2].no + " " + exampleData[3].no + " " + exampleData[4].no + " " + exampleData[5].no + " ";
	//grafikKWz(exampleData, 'tahuIsi', 100, "", 1, 10, 10);
	//grafikParam(dataChart, lokasi, hmax, hmin, labelY, periode, posX, posY);
	//grafikParam(exampleData, 'tahuIsi', 100, 0, "", 1, 0, 0);
	grafikKWz(exampleData, 'tahuIsi', 100, 0, "", 1, 10, 10);
}

function desimal(nilai,angkapenting) {
	var hasil;
	if (nilai.indexOf('.')>0) {
		return (nilai.substring(nilai.indexOf('.')+angkapenting+1,0));
		//return nilai.toFixed(angkapenting);
	} else
		return nilai;
}

function grafikKWz(dataChart, lokasi, hmax, hmin, labelY, periode, posX, posY, selang) {
//*
	var obj;
	var bwh = hmin;
	
	var store = new dojo.collections.Store();
	store.setData(dataChart);

	var timeSeries = new dojo.charting.Series({
		dataSource: store, bindings: { x: "no", y: "nilai" }, label: "Example Series"
	}); 
	
	//Define the x-axis
	var xAxis = new dojo.charting.Axis();

	//Set the upper and lower data range values
	xAxis.range = { lower: dataChart[0].no, upper: dataChart[dataChart.length-1].no	 };

	xAxis.origin 	= "max";
	xAxis.showLines = true;
	xAxis.showTicks = true;
	xAxis.label 	= "waktu "+selang;

	//Setup the x tick marks on the chart
	var lblX = {};	
	for (j=(dataChart.length)-1; j>0; j--) {
	//for (j=0; j<(arHistori.length); j++) {
		//lbl = {label: (dataChart[j].no), value: dataChart[j].no};
		lbl = {label: j, value: (dataChart.length-j)};
		(xAxis.labels).push(lbl);	
	}
	lbl = {label: "now", value: (dataChart.length)};
	(xAxis.labels).push(lbl);	
	
	//Define the y-axis
	var yAxis = new dojo.charting.Axis();
	yAxis.range = { lower: bwh, upper: hmax };
	yAxis.showLines = true;
	yAxis.showTicks = true;
	yAxis.label = labelY;

	//Setup the y tick marks on the chart
	var lblY = [];
	
	var grid = (hmax-bwh)/5;
	for(k=0; k<6; k++) {
		obj = {label: (k*grid+bwh).toString(), value: (k*grid)+bwh};
		(yAxis.labels).push(obj);
	}
	//document.getElementById('tahuIsi').innerHTML += (yAxis.labels)[3].value + "<br>";
	
	var chartPlot = new dojo.charting.Plot(xAxis, yAxis);

	chartPlot.addSeries({
		data: timeSeries, plotter: dojo.charting.Plotters.CurvedArea
	}); 

	var chartPlotArea = new dojo.charting.PlotArea();
	chartPlotArea.size = { width: 370, height: 170 };
	chartPlotArea.padding = { top: 20, right: 20, bottom: 35, left: 40 };

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

function grafikParam(dataChart, lokasi, hmax, hmin, labelY, periode, posX, posY) {
	var bwh = hmin;
	var tinggi = 5;
	
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
	for (j=(dataChart.length); j>0; j--) {
		lbl = {label: j, value: (dataChart.length-j)};
		(xAxis.labels).push(lbl);	
	}
	lbl = {label: "now", value: (dataChart.length)};
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
	
	chartPlotArea.size = { width: 370, height: 170 };
	chartPlotArea.padding = { top: 20, right: 20, bottom: 35, left: 50 };
	
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
