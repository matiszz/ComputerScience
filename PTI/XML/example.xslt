<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="rental">
		<html>
			<head>
				<title><xsl:value-of select="make"/> <xsl:value-of select="model"/></title>
			</head>
			<body>
				<h1><xsl:value-of select="make"/></h1><br />
				<h2><xsl:value-of select="model"/></h2><br />
				<table border="0">
					<tr><td>Number of days:</td><td><xsl:value-of select="nofdays"/></td></tr>
					<tr><td>Units:</td><td><xsl:value-of select="nofunits"/></td></tr>
					<tr><td>Discount:</td><td><xsl:value-of select="discount"/></td></tr>
				</table>
			</body>
		</html>
	</xsl:template>
</xsl:stylesheet>