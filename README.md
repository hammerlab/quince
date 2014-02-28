quince
======

Scalable genome variant analytics using [BDG-formatted](https://github.com/bigdatagenomics/bdg-formats) data.

This repository is designed to show some downstream applications, once you have
an analysis-ready VCF and any annotations of interest. This will especially be
targeting using Impala for genome analysis, but not limited to it.  Types of
things you might find here:

* UDFs for feature extraction and statistics (perhaps some PLINK-like
functionality)

* Patterns for ingesting common data sets and performing analysis in SQL;
integration with annotation data

* Working with eQTL data

* Support (UCSC) browser-like functionality

Contributions are welcome.

## Examples

*Example 1*

Contains a variant data schema being experimented with by the Broad Institute.
Includes UDFs to generate the proper fields.
