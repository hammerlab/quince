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

Then convert to Avro using the VCFtoParquet impl:

    hadoop jar vcf-0.1.0-jar-with-dependencies.jar \
        com.cloudera.science.vcf.VCFtoParquetDriver \
        -D mapred.child.java.opts=-Xmx4096M \
        -D mapreduce.map.java.opts=-Xmx4096M \
        -D mapreduce.map.memory.mb=4096 \
        flat \
        hdfs:///user/laserson/1kg/vcf \
        hdfs:///user/laserson/1kg/parquet_unpartitioned

xPlace the schema somewhere in HFDS:
x
x    hadoop jar vcf-0.1.0-jar-with-dependencies.jar \
x        com.cloudera.science.vcf.VCFtoAvroSchema \
x        flat \
x        hdfs:///user/laserson/1kg/vcf
x
xRegister table with Hive:
x
x    SET hive.exec.compress.output=true;
x    SET avro.output.codec=snappy;
x    
x    CREATE EXTERNAL TABLE 1kg_avro
x    ROW FORMAT
x        SERDE 'org.apache.hadoop.hive.serde2.avro.AvroSerDe'
x    STORED AS
x        INPUTFORMAT 'org.apache.hadoop.hive.ql.io.avro.AvroContainerInputFormat'
x        OUTPUTFORMAT 'org.apache.hadoop.hive.ql.io.avro.AvroContainerOutputFormat'
x    LOCATION '/user/laserson/1kg/avro'
x    TBLPROPERTIES ('avro.schema.url'='hdfs:///user/laserson/1kg/schemas/1kg.flat.avsc');

In Impala, rewrite as partitioned Parquet table:

    CREATE TABLE 1kg_parquet (
        VCF_CHROM_INTERNAL STRING,
        VCF_POS INT,
        VCF_ID STRING,
        VCF_REF STRING,
        VCF_ALT STRING,
        VCF_QUAL DOUBLE,
        VCF_SAMPLE STRING,
        VCF_FILTER STRING,
        VCF_INFO_LDAF DOUBLE,
        VCF_INFO_AVGPOST DOUBLE,
        VCF_INFO_RSQ DOUBLE,
        VCF_INFO_ERATE DOUBLE,
        VCF_INFO_THETA DOUBLE,
        VCF_INFO_CIEND STRING,
        VCF_INFO_CIPOS STRING,
        VCF_INFO_END INT,
        VCF_INFO_HOMLEN STRING,
        VCF_INFO_HOMSEQ STRING,
        VCF_INFO_SVLEN INT,
        VCF_INFO_SVTYPE STRING,
        VCF_INFO_AC STRING,
        VCF_INFO_AN INT,
        VCF_INFO_AA STRING,
        VCF_INFO_AF DOUBLE,
        VCF_INFO_AMR_AF DOUBLE,
        VCF_INFO_ASN_AF DOUBLE,
        VCF_INFO_AFR_AF DOUBLE,
        VCF_INFO_EUR_AF DOUBLE,
        VCF_INFO_VT STRING,
        VCF_INFO_SNPSOURCE STRING,
        VCF_CALL_GT STRING,
        VCF_CALL_DS DOUBLE,
        VCF_CALL_GL STRING
    )
    PARTITIONED BY (VCF_CHROM STRING, SEGMENT INT)
    STORED AS PARQUET;

    INSERT OVERWRITE TABLE 1kg_parquet
    PARTITION (VCF_CHROM, SEGMENT)
    [SHUFFLE]
    SELECT
        *,
        VCF_CHROM,
        CAST(FLOOR(VCF_POS / 10000000.) AS INT)
    FROM
        1kg_parquet_unpartitioned;
