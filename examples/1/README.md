This follows the Broad schema for their scalable variant store tests.

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

Then convert to Parquet using the VCFtoParquet impl:

    hadoop jar vcf-0.1.0-jar-with-dependencies.jar \
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

In Impala, rewrite as partitioned Parquet table with Broad schema:

    CREATE TABLE 1kg_broad (
        CHROM_INTERNAL STRING,
        POS INT,
        _ID_ STRING,
        SAMPLE STRING,
        GT INT,
        NC BOOLEAN,
        TYPE STRING,
        IS_TI BOOLEAN,
        IS_INS BOOLEAN,
        LHET DOUBLE,
        LHREF DOUBLE,
        LHVAR DOUBLE
    )
    PARTITIONED BY (CHROM STRING, SEGMENT INT)
    STORED AS PARQUET;

    # This insert is split in half because of memory constraints
    
    INSERT OVERWRITE TABLE 1kg_broad
    PARTITION (CHROM, SEGMENT)
    [SHUFFLE]
    SELECT
        VCF_CHROM,
        VCF_POS,
        GenerateId(VCF_CHROM, VCF_POS, VCF_REF, VCF_ALT),
        VCF_SAMPLE,
        GenotypeAsInt(VCF_CALL_GT),
        NoCall(VCF_CALL_GT),
        VCF_INFO_VT,
        IsTransition(VCF_REF, VCF_ALT),
        IsInsertion(VCF_INFO_VT, VCF_REF, VCF_ALT),
        pow(10, LogLikelihoodHet(VCF_CALL_GL)),
        pow(10, LogLikelihoodRef(VCF_CALL_GL)),
        pow(10, LogLikelihoodAlt(VCF_CALL_GL)),
        VCF_CHROM,
        ChrSegment(VCF_POS, 1000)
    FROM
        1kg_parquet_unpartitioned
    WHERE
        (VCF_CHROM = '1' OR VCF_CHROM = '2' OR VCF_CHROM = '3' OR VCF_CHROM = '3'
        OR VCF_CHROM = '5' OR VCF_CHROM = '6' OR VCF_CHROM = '7' OR VCF_CHROM = '8');
    
    INSERT INTO TABLE 1kg_broad
    PARTITION (VCF_CHROM, SEGMENT)
    [SHUFFLE]
    SELECT
        VCF_CHROM,
        VCF_POS,
        GenerateId(VCF_CHROM, VCF_POS, VCF_REF, VCF_ALT),
        VCF_SAMPLE,
        GenotypeAsInt(VCF_CALL_GT),
        NoCall(VCF_CALL_GT),
        VCF_INFO_VT,
        IsTransition(VCF_REF, VCF_ALT),
        IsInsertion(VCF_INFO_VT, VCF_REF, VCF_ALT),
        pow(10, LogLikelihoodHet(VCF_CALL_GL)),
        pow(10, LogLikelihoodRef(VCF_CALL_GL)),
        pow(10, LogLikelihoodAlt(VCF_CALL_GL)),
        VCF_CHROM,
        ChrSegment(VCF_POS, 1000)
    FROM
        1kg_parquet_unpartitioned
    WHERE
        (VCF_CHROM != '1' AND VCF_CHROM != '2' AND VCF_CHROM != '3' AND VCF_CHROM != '3'
        AND VCF_CHROM != '5' AND VCF_CHROM != '6' AND VCF_CHROM != '7' AND VCF_CHROM != '8');
