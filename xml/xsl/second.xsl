<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="html" />
    <xsl:template match="/">
        <html>
            <body>
                <h1>Tiobe HOF</h1>
                <ol>
                    <xsl:apply-templates select="hof/entry">
                        <xsl:sort select="year" data-type="number" />
                    </xsl:apply-templates>
                </ol>
            </body>
        </html>
    </xsl:template>

    <xsl:template match="entry">
        <xsl:if test="year &gt;= 2010">
            <li>
                <ul>
                    <xsl:apply-templates select="year" />
                    <xsl:apply-templates select="winner" />
                </ul>
            </li>
        </xsl:if>
    </xsl:template>

    <xsl:template match="year">
        <li>Year: <xsl:value-of select="." /></li>
    </xsl:template>

    <xsl:template match="winner">
        <li>Winner: <xsl:value-of select="." /></li>
    </xsl:template>
</xsl:stylesheet>
