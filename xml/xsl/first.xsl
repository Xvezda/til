<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="html" />
    <xsl:template match="/">
        <html>
            <body>
                <h1>XSL Version of HOF</h1>
                <table>
                    <tr>
                        <th>Year</th>
                        <th>Winner</th>
                    </tr>
                    <xsl:for-each select="hof/entry">
                        <tr>
                            <td><xsl:value-of select="year" /></td>
                            <td><xsl:value-of select="winner" /></td>
                        </tr>
                    </xsl:for-each>
                </table>
            </body>
        </html>
    </xsl:template>
</xsl:stylesheet>
