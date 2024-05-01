var page = require('webpage').create();
/*page.viewportSize = {
	width: 1920,
	height: 1080
};*/
page.open('./doc.html', function() {
	page.render('doc.png');
	phantom.exit();
});
