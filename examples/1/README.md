## Broad scalable variant store benchmarking

This follows the Broad schema for their scalable variant store tests.


### The hardware

This is running on a cluster of 6 physical machines.  Each machine:

* 60 GB memory

* 11 hard disks for HDFS use

* 24 cores


### ETL

First download the 1000 Genome VCF data into HDFS like so (this can be
parallelized across the cluster):

    curl -s ftp://ftp-trace.ncbi.nih.gov/1000genomes/ftp/release/20110521/ALL.chr16.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf.gz | gunzip | hadoop fs -put - /user/laserson/1kg/vcf/ALL.chr16.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf
    curl -s ftp://ftp-trace.ncbi.nih.gov/1000genomes/ftp/release/20110521/ALL.chr10.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf.gz | gunzip | hadoop fs -put - /user/laserson/1kg/vcf/ALL.chr10.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf
    curl -s ftp://ftp-trace.ncbi.nih.gov/1000genomes/ftp/release/20110521/ALL.chr7.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf.gz | gunzip | hadoop fs -put - /user/laserson/1kg/vcf/ALL.chr7.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf
    curl -s ftp://ftp-trace.ncbi.nih.gov/1000genomes/ftp/release/20110521/ALL.chr3.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf.gz | gunzip | hadoop fs -put - /user/laserson/1kg/vcf/ALL.chr3.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf
    curl -s ftp://ftp-trace.ncbi.nih.gov/1000genomes/ftp/release/20110521/ALL.chr19.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf.gz | gunzip | hadoop fs -put - /user/laserson/1kg/vcf/ALL.chr19.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf
    curl -s ftp://ftp-trace.ncbi.nih.gov/1000genomes/ftp/release/20110521/ALL.chr2.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf.gz | gunzip | hadoop fs -put - /user/laserson/1kg/vcf/ALL.chr2.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf
    curl -s ftp://ftp-trace.ncbi.nih.gov/1000genomes/ftp/release/20110521/ALL.chr21.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf.gz | gunzip | hadoop fs -put - /user/laserson/1kg/vcf/ALL.chr21.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf
    curl -s ftp://ftp-trace.ncbi.nih.gov/1000genomes/ftp/release/20110521/ALL.chr20.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf.gz | gunzip | hadoop fs -put - /user/laserson/1kg/vcf/ALL.chr20.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf
    curl -s ftp://ftp-trace.ncbi.nih.gov/1000genomes/ftp/release/20110521/ALL.chr4.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf.gz | gunzip | hadoop fs -put - /user/laserson/1kg/vcf/ALL.chr4.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf
    curl -s ftp://ftp-trace.ncbi.nih.gov/1000genomes/ftp/release/20110521/ALL.chr14.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf.gz | gunzip | hadoop fs -put - /user/laserson/1kg/vcf/ALL.chr14.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf
    curl -s ftp://ftp-trace.ncbi.nih.gov/1000genomes/ftp/release/20110521/ALL.chr5.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf.gz | gunzip | hadoop fs -put - /user/laserson/1kg/vcf/ALL.chr5.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf
    curl -s ftp://ftp-trace.ncbi.nih.gov/1000genomes/ftp/release/20110521/ALL.chrX.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf.gz | gunzip | hadoop fs -put - /user/laserson/1kg/vcf/ALL.chrX.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf
    curl -s ftp://ftp-trace.ncbi.nih.gov/1000genomes/ftp/release/20110521/ALL.chr12.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf.gz | gunzip | hadoop fs -put - /user/laserson/1kg/vcf/ALL.chr12.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf
    curl -s ftp://ftp-trace.ncbi.nih.gov/1000genomes/ftp/release/20110521/ALL.chr8.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf.gz | gunzip | hadoop fs -put - /user/laserson/1kg/vcf/ALL.chr8.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf
    curl -s ftp://ftp-trace.ncbi.nih.gov/1000genomes/ftp/release/20110521/ALL.chr6.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf.gz | gunzip | hadoop fs -put - /user/laserson/1kg/vcf/ALL.chr6.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf
    curl -s ftp://ftp-trace.ncbi.nih.gov/1000genomes/ftp/release/20110521/ALL.chr18.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf.gz | gunzip | hadoop fs -put - /user/laserson/1kg/vcf/ALL.chr18.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf
    curl -s ftp://ftp-trace.ncbi.nih.gov/1000genomes/ftp/release/20110521/ALL.chr11.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf.gz | gunzip | hadoop fs -put - /user/laserson/1kg/vcf/ALL.chr11.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf
    curl -s ftp://ftp-trace.ncbi.nih.gov/1000genomes/ftp/release/20110521/ALL.chr9.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf.gz | gunzip | hadoop fs -put - /user/laserson/1kg/vcf/ALL.chr9.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf
    curl -s ftp://ftp-trace.ncbi.nih.gov/1000genomes/ftp/release/20110521/ALL.chr17.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf.gz | gunzip | hadoop fs -put - /user/laserson/1kg/vcf/ALL.chr17.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf
    curl -s ftp://ftp-trace.ncbi.nih.gov/1000genomes/ftp/release/20110521/ALL.chr22.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf.gz | gunzip | hadoop fs -put - /user/laserson/1kg/vcf/ALL.chr22.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf
    curl -s ftp://ftp-trace.ncbi.nih.gov/1000genomes/ftp/release/20110521/ALL.chr13.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf.gz | gunzip | hadoop fs -put - /user/laserson/1kg/vcf/ALL.chr13.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf
    curl -s ftp://ftp-trace.ncbi.nih.gov/1000genomes/ftp/release/20110521/ALL.chr15.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf.gz | gunzip | hadoop fs -put - /user/laserson/1kg/vcf/ALL.chr15.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf
    curl -s ftp://ftp-trace.ncbi.nih.gov/1000genomes/ftp/release/20110521/ALL.chr1.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf.gz | gunzip | hadoop fs -put - /user/laserson/1kg/vcf/ALL.chr1.phase1_release_v3.20101123.snps_indels_svs.genotypes.vcf

This data takes up 1.1 TB uncompressed.

Then convert to Parquet using the [VCFtoParquet impl](https://github.com/laserson/vcf2parquet):

    hadoop jar vcf2parquet-0.1.0-jar-with-dependencies.jar \
        com.cloudera.science.vcf.VCFtoParquetDriver \
        -D mapred.child.java.opts=-Xmx4096M \
        -D mapreduce.map.java.opts=-Xmx4096M \
        -D mapreduce.map.memory.mb=4096 \
        flat \
        hdfs:///user/laserson/1kg/vcf \
        hdfs:///user/laserson/1kg/parquet_unpartitioned

Compile the UDFs for the Broad schema and register them in Impala

    cd examples/1/src
    cmake .
    make
    register-impala-udfs.py -i build/broad.ll -o /user/laserson/udfs/broad.ll \
            -j bottou01-10g.pa.cloudera.com -k bottou01-10g.pa.cloudera.com \
            -u laserson -d laserson -f \
            -n GenerateId -t STRING \
            -n GenotypeAsInt -t INT \
            -n LogLikelihoodRef -t DOUBLE \
            -n LogLikelihoodHet -t DOUBLE \
            -n LogLikelihoodAlt -t DOUBLE \
            -n IsTransition -t BOOLEAN \
            -n IsInsertion -t BOOLEAN \
            -n NoCall -t BOOLEAN

Also make sure the chromosome segment UDF is registered (quince.h):

    cd impala
    cmake .
    make
    register-impala-udfs.py -i build/quince.ll -o /user/laserson/udfs/quince.ll \
            -j bottou01-10g.pa.cloudera.com -k bottou01-10g.pa.cloudera.com \
            -u laserson -d laserson -f \
            -n ChrSegment -t INT

In Impala, rewrite as unpartitioned Parquet table with Broad schema:

```sql
CREATE TABLE 1kg_broad_unpartitioned (
    CHROM STRING,
    POS INT,
    SAMPLE STRING,
    GT INT,
    NC BOOLEAN,
    TYPE STRING,
    IS_TI BOOLEAN,
    IS_INS BOOLEAN,
    LOGLHET DOUBLE,
    LOGLHREF DOUBLE,
    LOGLHVAR DOUBLE
)
STORED AS PARQUET;

INSERT OVERWRITE TABLE 1kg_broad_unpartitioned
SELECT
    VCF_CHROM,
    VCF_POS,
    VCF_SAMPLE,
    GenotypeAsInt(VCF_CALL_GT),
    NoCall(VCF_CALL_GT),
    VCF_INFO_VT,
    IsTransition(VCF_REF, VCF_ALT),
    IsInsertion(VCF_INFO_VT, VCF_REF, VCF_ALT),
    LogLikelihoodHet(VCF_CALL_GL),
    LogLikelihoodRef(VCF_CALL_GL),
    LogLikelihoodAlt(VCF_CALL_GL)
FROM
    1kg_parquet_unpartitioned;
```

And a partitioned version, but you need lots of memory for this:

```sql
CREATE TABLE 1kg_broad (
    CHROM_INTERNAL STRING,
    POS INT,
    SAMPLE STRING,
    GT INT,
    NC BOOLEAN,
    TYPE STRING,
    IS_TI BOOLEAN,
    IS_INS BOOLEAN,
    LOGLHET DOUBLE,
    LOGLHREF DOUBLE,
    LOGLHVAR DOUBLE
)
PARTITIONED BY (CHROM STRING, SEGMENT INT)
STORED AS PARQUET;

# This insert is split in half because of memory constraints

INSERT OVERWRITE TABLE 1kg_broad
PARTITION (CHROM, SEGMENT)
[SHUFFLE]
SELECT
    *,
    CHROM,
    ChrSegment(POS, 10000)
FROM
    1kg_broad_unpartitioned
WHERE
    (CHROM = '1' OR CHROM = '2' OR CHROM = '3' OR CHROM = '3'
    OR CHROM = '5' OR CHROM = '6' OR CHROM = '7' OR CHROM = '8');

INSERT INTO TABLE 1kg_broad
PARTITION (CHROM, SEGMENT)
[SHUFFLE]
SELECT
    *,
    CHROM,
    ChrSegment(POS, 10000)
FROM
    1kg_broad_unpartitioned
WHERE
    (CHROM != '1' AND CHROM != '2' AND CHROM != '3' AND CHROM != '3'
    AND CHROM != '5' AND CHROM != '6' AND CHROM != '7' AND CHROM != '8');
```

This inserted a total of 43,359,732,780 rows taking up 175 GB.

Finally, the queries.


### NALT

Number of genotype calls that are not homozygous reference for each sample.

```sql
SELECT
    SAMPLE,
    COUNT(*) AS NALT
FROM
    1kg_broad
WHERE
    (NC = FALSE AND
    TYPE = 'SNP' AND
    (GT = 1 OR GT = 2))
GROUP BY
    SAMPLE
ORDER BY NALT DESC LIMIT 100;
```

Results across all 1kg data in 143 seconds:

    +---------+---------+
    | sample  | nalt    |
    +---------+---------+
    | NA19470 | 4396532 |
    | NA19399 | 4386662 |
    | NA19396 | 4381947 |
    | NA19469 | 4380314 |
    | NA19445 | 4375195 |
    ...

The query for chr20 alone adds an additional CHROM = '20' predicate.  It runs in
14 seconds.


### NHET

Number of heterozygout genotype calls for each sample.

```sql
SELECT
    SAMPLE,
    COUNT(*) AS NHET
FROM
    1kg_broad
WHERE
    (NC = FALSE AND
    TYPE = 'SNP' AND
    GT = 1)
GROUP BY
    SAMPLE
ORDER BY NHET DESC LIMIT 5;
```

Results across all 1kg in 94 seconds.

    +---------+---------+
    | sample  | nhet    |
    +---------+---------+
    | NA19036 | 2955212 |
    | NA19470 | 2948800 |
    | NA19185 | 2935175 |
    | NA19469 | 2933632 |
    | NA19399 | 2932718 |
    +---------+---------+

Results across chr20 in 15 seconds.


### SING

Total number of singletons per sample.

```sql
SELECT
    SAMPLE,
    COUNT(*) AS SING
FROM
    1kg_broad A
INNER JOIN
    (SELECT
        CHROM,
        POS
    FROM
        1kg_broad
    WHERE
        (NC = FALSE AND
        (GT = 1 OR GT = 2))
    GROUP BY
        CHROM,
        POS
    HAVING
        COUNT(*) = 1) B
ON (A.CHROM = B.CHROM AND A.POS = B.POS)
WHERE
    (NC = FALSE AND
    (GT = 1 OR GT = 2))
GROUP BY
    SAMPLE
ORDER BY SING DESC LIMIT 10;
```

Results across all 1kg data in 185 s.


### TITV

Transition/transversion ratio

```sql
SELECT
    SAMPLE,
    SUM(TI),
    SUM(TV),
    FLOOR(100*SUM(TI)/(SUM(TV)+0.5))/100 AS TITV
FROM
    (SELECT
        SAMPLE,
        CASE WHEN IS_TI = FALSE THEN 0 WHEN GT = 1 THEN 1 WHEN GT = 2 THEN 2 END AS TI,
        CASE WHEN IS_TI = TRUE  THEN 0 WHEN GT = 1 THEN 1 WHEN GT = 2 THEN 2 END AS TV
    FROM
        1kg_broad
    WHERE
        (NC = FALSE AND
        TYPE = 'SNP' AND
        (GT = 1 OR GT = 2))) A
GROUP BY
    SAMPLE
ORDER BY TITV DESC LIMIT 10;
```
    
Results for full 1kg data set in 163 seconds.

    +---------+---------+---------+------+
    | sample  | sum(ti) | sum(tv) | titv |
    +---------+---------+---------+------+
    | NA19020 | 3753466 | 1759417 | 2.13 |
    | NA19308 | 3769419 | 1777099 | 2.12 |
    | NA19117 | 3732921 | 1758259 | 2.12 |
    | NA19309 | 3767522 | 1776262 | 2.12 |
    | NA20359 | 3740531 | 1762172 | 2.12 |
    ...

Results for chr20 in 14 seconds.


### AvgPvREF

```sql
SELECT
    SAMPLE,
    AVG(POW(10, LOGLHREF)) AS AVG_P_HET
FROM
    1kg_broad
WHERE
    NC = FALSE AND
    TYPE = 'SNP' AND
    GT = 1
GROUP BY
    SAMPLE
ORDER BY AVG_P_HET DESC LIMIT 10;
```

Results for 1kg data set in 250 seconds.

    +---------+--------------------+
    | sample  | avg_p_het          |
    +---------+--------------------+
    | NA12043 | 0.2394731534932459 |
    | NA18912 | 0.2289868782408353 |
    | HG00155 | 0.2262393530704589 |
    | NA12287 | 0.2168919201217721 |

Results for chr20 data set in 16 seconds.


### Summary of results

| Query    | Full 1kg (sec) | Chr 20 only (sec) |
| :------- | -------------: | ----------------: |
| NALT     | 143            | 14                |
| NHET     | 94             | 15                |
| SING     | 185            | n/a               |
| TITV     | 163            | 14                |
| AvgPvREF | 250            | 16                |