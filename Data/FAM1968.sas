
/*************************************************************************
   Label           : 1968 Family Data: Final Release
   Rows            : 4802
   Columns         : 447
   ASCII File Date : December 5, 2013
*************************************************************************/

DATA FAM1968 ; 
   ATTRIB 
      V1        LABEL="RELEASE NUMBER"                                   format=f1.
      V2        LABEL="INTERVIEW NUMBER 68"                              format=f5.
      V3        LABEL="FAMILY NUMBER"                                    format=f4.
      V4        LABEL="SUBFAMILY NUMBER 68"                              format=f1.
      V5        LABEL="HOUSE VALUE"                                      format=f5.
      V6        LABEL="YRLY PROP TAXES"                                  format=f4.
      V7        LABEL="ACCURACY OF PR TAX"                               format=f1.
      V8        LABEL="YRLY MDRT PAYTS"                                  format=f4.
      V9        LABEL="ACCURACY OF MTG PTS"                              format=f1.
      V10       LABEL="YRLY RENT PAYTS"                                  format=f4.
      V11       LABEL="ACCURACY RENT PTS"                                format=f1.
      V12       LABEL="YRLY RENT VALUE"                                  format=f4.
      V13       LABEL="ACCURACY OF RNT VAL"                              format=f1.
      V14       LABEL="YRLY UTILITY PTS"                                 format=f3.
      V15       LABEL="ACCURACY OF UTIL"                                 format=f1.
      V16       LABEL="A+R DONE SELF"                                    format=f4.
      V17       LABEL="ACCURACY OF A+R SLF"                              format=f1.
      V18       LABEL="YRLY A+R PAYTS"                                   format=f4.
      V19       LABEL="ACCURACY OF A+R PT"                               format=f1.
      V20       LABEL="YRLY CAR INSUR"                                   format=f4.
      V21       LABEL="ACCURACY OF CAR INS"                              format=f1.
      V22       LABEL="YRLY CAR PAYTS"                                   format=f4.
      V23       LABEL="ACCURACY OF CAR PTS"                              format=f1.
      V24       LABEL="SAVD ON CAR REPR"                                 format=f4.
      V25       LABEL="ACCURACY OF SVD CAR"                              format=f1.
      V26       LABEL="TIME ON CAR REPR"                                 format=f3.
      V27       LABEL="ACCURCY OF TIME C.R."                             format=f1.
      V28       LABEL="OTHR PAYTS YRLY"                                  format=f4.
      V29       LABEL="ACCURACY OF OTHR PT"                              format=f1.
      V30       LABEL="FAMILY SIZE"                                      format=f1.
      V31       LABEL="YRLY FOOD STD."                                   format=f4.
      V32       LABEL="YRLY NEED STD"                                    format=f5.
      V33       LABEL="YRLY ALCOHOL"                                     format=f3.
      V34       LABEL="ACCURACY OF ALC"                                  format=f1.
      V35       LABEL="YRLY CIG EXP"                                     format=f3.
      V36       LABEL="ACCURCY OF CIG EXP"                               format=f1.
      V37       LABEL="YRLY FOOD BILL"                                   format=f4.
      V38       LABEL="ACCURACY OF FOOD"                                 format=f1.
      V39       LABEL="YRLY FOOD GROWN"                                  format=f3.
      V40       LABEL="ACCURACY OF FD GRN"                               format=f1.
      V41       LABEL="YRLY SAVD SEWING"                                 format=f3.
      V42       LABEL="ACCURACY OF SVD SEW"                              format=f1.
      V43       LABEL="YRLY FOOD ON JOB"                                 format=f3.
      V44       LABEL="ACCURACY FOOD JOB"                                format=f1.
      V45       LABEL="YRLY FOOD STAMPS"                                 format=f3.
      V46       LABEL="ACCURACY FOOD STPS"                               format=f1.
      V47       LABEL="YRLY HEADS HRS"                                   format=f4.
      V48       LABEL="ACCURACY:HDS HRS"                                 format=f1.
      V49       LABEL="HRS UNEMPL HEAD"                                  format=f4.
      V50       LABEL="ACCURACY UNEMP HEAD"                              format=f1.
      V51       LABEL="HRS HEAD ILL"                                     format=f4.
      V52       LABEL="ACCURACY HEAD ILL"                                format=f1.
      V53       LABEL="YRLY WIFE HRS"                                    format=f4.
      V54       LABEL="ACCURACY WIFE HRS"                                format=f1.
      V55       LABEL="PD CHILD CARE$"                                   format=f4.
      V56       LABEL="ACCURACY PD CARE"                                 format=f1.
      V57       LABEL="FREE HELP HRS"                                    format=f4.
      V58       LABEL="ACCURACY FREE HELP"                               format=f1.
      V59       LABEL="H& W HOUSEWORK"                                   format=f4.
      V60       LABEL="ACCURACY H& W HSWK"                               format=f1.
      V61       LABEL="HRS HOME PRODON"                                  format=f4.
      V62       LABEL="ACCURACY HOME PRODN"                              format=f1.
      V63       LABEL="OTHERS HSWK"                                      format=f4.
      V64       LABEL="ACCURACY OTH HSWK"                                format=f1.
      V65       LABEL="YRLY H& W WK HRS"                                 format=f4.
      V66       LABEL="ACCURACY H& W WK HRS"                             format=f1.
      V67       LABEL="1ST OTHR WORK HRS"                                format=f4.
      V68       LABEL="ACCURACY 1ST OTH WK"                              format=f1.
      V69       LABEL="2ND OTHR WORK HRS"                                format=f4.
      V70       LABEL="ACCURACY 2ND OTH WK"                              format=f1.
      V71       LABEL="NO OF MAJOR ADULTS"                               format=f1.
      V72       LABEL="TOT OTHR WRK HRS"                                 format=f4.
      V73       LABEL="LEISURE HRS/M.A."                                 format=f4.
      V74       LABEL="HDS LABOR INCOME"                                 format=f5.
      V75       LABEL="WIFE LBR INCOME"                                  format=f5.
      V76       LABEL="H& W TAXBL INCOME"                                format=f5.
      V77       LABEL="1ST OTHR TXL INC"                                 format=f5.
      V78       LABEL="2ND OTHR TXL INC"                                 format=f4.
      V79       LABEL="TOT OTHERS INC"                                   format=f5.
      V80       LABEL="FAM TRANSFER INC"                                 format=f4.
      V81       LABEL="FAM MONEY INC"                                    format=f5.
      V82       LABEL="CONTRIB OUTS FU"                                  format=f4.
      V83       LABEL="FAM INC TAX"                                      format=f5.
      V84       LABEL="COST OF INCOME"                                   format=f5.
      V85       LABEL="ACCURACY:HD L INC"                                format=f1.
      V86       LABEL="ACCURACY:WIFE INC"                                format=f1.
      V87       LABEL="ACCURACY:H& W TINC"                               format=f1.
      V88       LABEL="ACCURACY:1ST OTH INC"                             format=f1.
      V89       LABEL="ACCURACY:2ND OTH INC"                             format=f1.
      V90       LABEL="ACCURACY:TRANSF INC"                              format=f1.
      V91       LABEL="ACCURACY CONTRIB"                                 format=f1.
      V92       LABEL="SRC PR SAMPL UN"                                  format=f3.
      V93       LABEL="STATE (68)"                                       format=f2.
      V94       LABEL="COUNTY(68)"                                       format=f1.
      V95       LABEL="SIZ LGST CTY PSU"                                 format=f1.
      V96       LABEL="LOCAL OR CPS FU #"                                format=f1.
      V97       LABEL="INTRVWR SOC SEC"                                  format=f9.
      V98       LABEL="INTRVWR INT NO"                                   format=f2.
      V99       LABEL="DATE OF INTVW"                                    format=f1.
      V100      LABEL="LNGTH OF INTVW"                                   format=f3.
      V101      LABEL="WHEN MOVED IN"                                    format=f1.
      V102      LABEL="HOW MANY ROOMS"                                   format=f1.
      V103      LABEL="OWN OR RENT"                                      format=f1.
      V104      LABEL="MORTGAGE?"                                        format=f1.
      V105      LABEL="WHY FREE HOUSING"                                 format=f1.
      V106      LABEL="WORK FOR HOUSING"                                 format=f1.
      V107      LABEL="ADD OR REPAIRS"                                   format=f1.
      V108      LABEL="WHAT A& R DONE"                                   format=f1.
      V109      LABEL="A& R DONE SELF"                                   format=f1.
      V110      LABEL="OWE ON A& R"                                      format=f1.
      V111      LABEL="MIGHT MOVE"                                       format=f1.
      V112      LABEL="WHY MIGHT MOVE"                                   format=f1.
      V113      LABEL="NUMBER IN DU"                                     format=f2.
      V114      LABEL="HHOLD COMPOSITION"                                format=f1.
      V115      LABEL="NUMBER IN FAMILY"                                 format=f2.
      V116      LABEL="NO ADULTS IN FAM"                                 format=f1.
      V117      LABEL="AGE OF HEAD"                                      format=f2.
      V118      LABEL="AGE OF WIFE"                                      format=f2.
      V119      LABEL="SEX OF HEAD"                                      format=f1.
      V120      LABEL="AGE YOUNGST CHILD"                                format=f1.
      V121      LABEL="NR CHLDRN IN SCHOOL"                              format=f1.
      V122      LABEL="NR CHLDRN LVNG AWAY"                              format=f1.
      V123      LABEL="NR CHLDRN IN INSTIT"                              format=f1.
      V124      LABEL="RQD NO ROOMS"                                     format=f1.
      V125      LABEL="NR CHLDRN 0-11GRDS"                               format=f1.
      V126      LABEL="NR CHLDRN 12GRDS"                                 format=f1.
      V127      LABEL="NR CHLDRN 13GRDS"                                 format=f1.
      V128      LABEL="NR MOVED IN"                                      format=f1.
      V129      LABEL="WHO MOVED IN"                                     format=f1.
      V130      LABEL="NR MOVED OUT"                                     format=f1.
      V131      LABEL="WHO MOVED OUT"                                    format=f1.
      V132      LABEL="CPS PR SAMPL UN"                                  format=f3.
      V133      LABEL="CPS HOUSEHOLD NR"                                 format=f4.
      V134      LABEL="CPS SEGMENT, PART"                                format=f1.
      V135      LABEL="CPS SEGMENT,REST"                                 format=f2.
      V136      LABEL="LAST PTO MTG"                                     format=f1.
      V137      LABEL="EDUC EXPT CHLDRN"                                 format=f1.
      V138      LABEL="AGE HD 1ST CHLD"                                  format=f2.
      V139      LABEL="NR CAR DRIVERS"                                   format=f1.
      V140      LABEL="DIFFIC FR NO CAR"                                 format=f1.
      V141      LABEL="WHAT DIFF NO CAR"                                 format=f1.
      V142      LABEL="ADEQ PUB TRANSP"                                  format=f1.
      V143      LABEL="NR CARS OWNED"                                    format=f1.
      V144      LABEL="YR OF NEWST CAR"                                  format=f2.
      V145      LABEL="VALUE OF CARS"                                    format=f4.
      V146      LABEL="CONDITION BEST COR"                               format=f1.
      V147      LABEL="CONDITION WORST COR"                              format=f1.
      V148      LABEL="OWE ON CAR"                                       format=f1.
      V149      LABEL="CAR INSURED"                                      format=f1.
      V150      LABEL="NR PAYTS LEFT"                                    format=f1.
      V151      LABEL="NR SETS OF PAYTS"                                 format=f1.
      V152      LABEL="CAR HAVE SEAT BELTS"                              format=f1.
      V153      LABEL="SEAT BELTS FASTENED"                              format=f1.
      V154      LABEL="DO OWN CAR REPAIR"                                format=f1.
      V155      LABEL="KINDS OF CAR REPAIR"                              format=f1.
      V156      LABEL="AMT SAVD CAR REPAIR"                              format=f1.
      V157      LABEL="TIME ON CAR REPAIR"                               format=f1.
      V158      LABEL="MEDICAL INSURANCE"                                format=f1.
      V159      LABEL="SAVINGS"                                          format=f1.
      V160      LABEL="1MONTHS INC SAVED"                                format=f1.
      V161      LABEL="2MO INC SVD 5YRS"                                 format=f1.
      V162      LABEL="EAT OUT OFTEN"                                    format=f1.
      V163      LABEL="SPEND EATING OUT"                                 format=f1.
      V164      LABEL="MILK DELIVERED"                                   format=f1.
      V165      LABEL="SPEND ON MILK DLVRD"                              format=f1.
      V166      LABEL="SPEND ON OTHR FOOD"                               format=f1.
      V167      LABEL="SPEND ON ALCOHOL"                                 format=f1.
      V168      LABEL="ALCHL IN FOOD BILL"                               format=f1.
      V169      LABEL="NR CIGS SMOKED"                                   format=f1.
      V170      LABEL="CIGS IN FOOD BILL"                                format=f1.
      V171      LABEL="1ST WAY KP FD BL DN"                              format=f1.
      V172      LABEL="2ND WAY KP FD BL DN"                              format=f1.
      V173_1    LABEL="WAYS KP FD BL DN RESP 1"                          format=f1.
      V173_2    LABEL="WAYS KP FD BL DN RESP 2"                          format=f1.
      V174      LABEL="HOW OFTN EAT TGTHR"                               format=f1.
      V175      LABEL="1ST WAY SV ON CLTHNG"                             format=f1.
      V176      LABEL="2ND WAY SV ON CLTHNG"                             format=f1.
      V177_1    LABEL="WAYS SV ON CLTHNG RESP 1"                         format=f1.
      V177_2    LABEL="WAYS SV ON CLTHNG RESP 2"                         format=f1.
      V178      LABEL="AMT SVD ON CLOTHING"                              format=f1.
      V179      LABEL="WHO AT INTERVIEW"                                 format=f1.
      V180      LABEL="WHO RESPONDENT"                                   format=f1.
      V181      LABEL="RACE"                                             format=f1.
      V182      LABEL="NR OF CALLS"                                      format=f1.
      V183      LABEL="HOW CLEAN DU"                                     format=f1.
      V184      LABEL="READING MTL IN DU"                                format=f1.
      V185      LABEL="NR QSTNS REPEATED"                                format=f1.
      V186      LABEL="NR REPLIES REPEATED"                              format=f1.
      V187      LABEL="R DISFIGURED"                                     format=f1.
      V188      LABEL="NEAREST SMSA"                                     format=f3.
      V189      LABEL="MILES TO CNTR CITY"                               format=f1.
      V190      LABEL="TYPE STRUCTURE"                                   format=f1.
      V191      LABEL="NEIGHBORHOOD LWST"                                format=f1.
      V192      LABEL="NEIGHBORHOOD HGHST"                               format=f1.
      V193      LABEL="PUBLIC HOUSING"                                   format=f1.
      V194      LABEL="HOUSING DEFECTS"                                  format=f1.
      V195      LABEL="WORD-SCORE"                                       format=f2.
      V196      LABEL="WORKING NOW"                                      format=f1.
      V197      LABEL="OCCUPATION"                                       format=f1.
      V197_A    LABEL="OCCUPATION OF HEAD         68"                    format=f3.
      V197_B    LABEL="INDUSTRY   OF HEAD         68"                    format=f3.
      V198      LABEL="SELF-EMPLOYED"                                    format=f1.
      V199      LABEL="OWN DECISIONS IMPT"                               format=f1.
      V200      LABEL="HOW LONG EMPLYR"                                  format=f1.
      V201      LABEL="HPND PREVC JOB"                                   format=f1.
      V202      LABEL="PRSNT JOB BETTER"                                 format=f1.
      V203      LABEL="NR EMPLYRS 10 YRS"                                format=f1.
      V204      LABEL="EVR MOVED FOR JOB"                                format=f1.
      V205      LABEL="EVR TURND DOWN JOB"                               format=f1.
      V206      LABEL="ABLE FIND STDY WK HR"                             format=f1.
      V207      LABEL="HOW GOOD JOB TO MOVE"                             format=f1.
      V208      LABEL="PLAN NEW JOB"                                     format=f1.
      V209      LABEL="KIND NEW JOB"                                     format=f1.
      V210      LABEL="MIGHT EARN NW JB"                                 format=f4.2
      V211      LABEL="NEED ADDTL TRNG"                                  format=f1.
      V212      LABEL="DOING ANYTHING NJB"                               format=f1.
      V213      LABEL="LIKE TOLD WHAT DO"                                format=f1.
      V214      LABEL="TROUBLE GET OTHR JB"                              format=f1.
      V215      LABEL="ILLNESS-ACCIDENT"                                 format=f1.
      V216      LABEL="DISABILITY"                                       format=f1.
      V217      LABEL="LATE TO WORK"                                     format=f1.
      V218      LABEL="SKIP WORK"                                        format=f1.
      V219      LABEL="UNEMPLYD-STRIKE"                                  format=f1.
      V220      LABEL="DAYS UNEMPL IN 68"                                format=f1.
      V221      LABEL="DAYS ILL OR UNABLE"                               format=f1.
      V222      LABEL="WEEKS VACATION H"                                 format=f1.
      V223      LABEL="WEEKS WORKED"                                     format=f1.
      V224      LABEL="STANDARD WEEK?"                                   format=f1.
      V225      LABEL="HRS IN STD WEEK"                                  format=f1.
      V226      LABEL="HRS OVERTIME"                                     format=f1.
      V227      LABEL="OTHER JOBS HD"                                    format=f1.
      V228      LABEL="OTHER OCCUP HD"                                   format=f1.
      V229      LABEL="$ PER HR 2ND JOB"                                 format=f4.2
      V230      LABEL="CD HAVE WKD MORE"                                 format=f1.
      V231      LABEL="WANTED MORE WORK"                                 format=f1.
      V232      LABEL="CD HAVE WORKED LESS"                              format=f1.
      V233      LABEL="WANTED LESS WORK"                                 format=f1.
      V234      LABEL="BKT TAXBL INC H& W"                               format=f1.
      V235      LABEL="NR PLACES NAME IN"                                format=f1.
      V236      LABEL="NR PLACES APPLIED"                                format=f1.
      V237      LABEL="JOBS NOT WORTH IT"                                format=f1.
      V238      LABEL="PAY ON BAD JOBS"                                  format=f4.2
      V239      LABEL="MARITAL STATUS"                                   format=f1.
      V240      LABEL="AGE HD 1ST MAR"                                   format=f2.
      V241      LABEL="HOW LONG WIDOWED"                                 format=f1.
      V242      LABEL="HOW CHILD CDRE"                                   format=f1.
      V243      LABEL="WIFES OCCUPATION"                                 format=f1.
      V243_A    LABEL="OCCUPATION OF WIFE         68"                    format=f3.
      V243_B    LABEL="INDUSTRY   OF WIFE         68"                    format=f3.
      V244      LABEL="WIFES WEEKS WKD"                                  format=f1.
      V245      LABEL="WIFES HRS/WEEK"                                   format=f1.
      V246      LABEL="WIFES EDUCATION"                                  format=f1.
      V247      LABEL="HDS FIRST MARRIAGE"                               format=f1.
      V248      LABEL="EXPECT CHILDREN?"                                 format=f1.
      V249      LABEL="GROSS RECTS FARM"                                 format=f1.
      V250      LABEL="BUSINESS INC?"                                    format=f1.
      V251      LABEL="HDS WAGES"                                        format=f1.
      V252      LABEL="HEAD OVERTIME"                                    format=f1.
      V253      LABEL="PROF PRAC INC H"                                  format=f1.
      V254      LABEL="FARM& ROOMER INC H"                               format=f1.
      V255      LABEL="DIV& INT& RENT INC-H"                             format=f1.
      V256      LABEL="ADC& ADCU INC-H"                                  format=f1.
      V257      LABEL="OTHER WELFARE-H"                                  format=f1.
      V258      LABEL="SOC SECURITY-H"                                   format=f1.
      V259      LABEL="OTHR PENSIONS H"                                  format=f1.
      V260      LABEL="UNEMPL COM& WC"                                   format=f1.
      V261      LABEL="ALIMONY"                                          format=f1.
      V262      LABEL="HELP FR RELATIVES"                                format=f1.
      V263      LABEL="WIFE INCOME TYPE"                                 format=f1.
      V264      LABEL="WIFE TOT INC"                                     format=f1.
      V265      LABEL="NR OTH INC RECRS"                                 format=f1.
      V266      LABEL="SETTLEMENT RECVD"                                 format=f1.
      V267      LABEL="SOURCE OF SETTLMNT"                               format=f1.
      V268      LABEL="FOOD, CLOTH AS PAY"                               format=f1.
      V269      LABEL="FOOD, CLOTH FREE"                                 format=f1.
      V270      LABEL="Y67 INCOME USUAL"                                 format=f1.
      V271      LABEL="WHY 67 UNUSUAL"                                   format=f1.
      V272      LABEL="INC VARY MONTHLY"                                 format=f1.
      V273      LABEL="WHY INC VARIES"                                   format=f1.
      V274      LABEL="BETTER OFF FIN"                                   format=f1.
      V275      LABEL="EXPENSES UNUSUAL"                                 format=f1.
      V276      LABEL="LIKELY CHANGES"                                   format=f1.
      V277      LABEL="CHANGES FOR BETTER"                               format=f1.
      V278      LABEL="DEPENDENTS NOT HERE"                              format=f1.
      V279      LABEL="WOULD HELP REL MORE"                              format=f1.
      V280      LABEL="DO IN SPARE TIME"                                 format=f1.
      V281      LABEL="2ND DO SPARE TIME"                                format=f1.
      V282_1    LABEL="BOTH USES OF TIME RESP 1"                         format=f1.
      V282_2    LABEL="BOTH USES OF TIME RESP 2"                         format=f1.
      V283      LABEL="NR OF TIME USES"                                  format=f1.
      V284      LABEL="HOW OFTEN CHURCH"                                 format=f1.
      V285      LABEL="TAKING COURSES"                                   format=f1.
      V286      LABEL="HOURS/DAY TV"                                     format=f1.
      V287      LABEL="HOW OFTEN NEWSP"                                  format=f1.
      V288      LABEL="NR NEIGHBORS KNOWN"                               format=f1.
      V289      LABEL="RELATIVES NEAR"                                   format=f1.
      V290      LABEL="HRS HELPING REL"                                  format=f1.
      V291      LABEL="HELP FROM OUTSIDE"                                format=f1.
      V292      LABEL="HOW OFTEN CLUBS"                                  format=f1.
      V293      LABEL="HOW OFTEN TAVERN"                                 format=f1.
      V294      LABEL="UNION AND DUES"                                   format=f1.
      V295      LABEL="FELT LIFE WORK OUT"                               format=f1.
      V296      LABEL="PLAN AHEAD"                                       format=f1.
      V297      LABEL="CARRY OUT PLANS"                                  format=f1.
      V298      LABEL="FINISH THINGS"                                    format=f1.
      V299      LABEL="LIKE CHALLENGE"                                   format=f1.
      V300      LABEL="SPEND OR SAVE"                                    format=f1.
      V301      LABEL="JOB LIKE,OR MONEY"                                format=f1.
      V302      LABEL="SATISFIED WITHSELF"                               format=f1.
      V303      LABEL="HAVE LIMITATIONS"                                 format=f1.
      V304      LABEL="GET ANGRY EASILY"                                 format=f1.
      V305      LABEL="MATTER OTHERS THINK"                              format=f1.
      V306      LABEL="TRUST MOST OTHERS"                                format=f1.
      V307      LABEL="FIGURE WAYS MORE$"                                format=f1.
      V308      LABEL="THINK ABOUT FUTURE"                               format=f1.
      V309      LABEL="LIFE GETTING BETTER"                              format=f1.
      V310      LABEL="UNDESERVED GOOD"                                  format=f1.
      V311      LABEL="WHERE H GREW UP"                                  format=f2.
      V312      LABEL="H GREW UP FARM"                                   format=f1.
      V313      LABEL="HEADS EDUCATION"                                  format=f1.
      V314      LABEL="HD OTHER TRAINING"                                format=f1.
      V315      LABEL="HEAD A VETERAN"                                   format=f1.
      V316      LABEL="NR SIBLINGS HEAD"                                 format=f1.
      V317      LABEL="HD PARENTS POOR"                                  format=f1.
      V318      LABEL="H FATHERS EDUCATION"                              format=f1.
      V319      LABEL="ACCURACY OF MORTG"                                format=f1.
      V320      LABEL="IMPUTED RENT"                                     format=f4.
      V321      LABEL="ACCURACY IMP RENT"                                format=f1.
      V322      LABEL="TOTAL REAL Y"                                     format=f5.
      V323      LABEL="REAL NET Y"                                       format=f5.
      V324      LABEL="REAL NET Y-HSNG"                                  format=f5.
      V325      LABEL="MONEY Y/NEEDS"                                    format=f5.2
      V326      LABEL="REAL NET Y/NEEDS"                                 format=f5.2
      V327      LABEL="REAL NET Y-HSNG/FD"                               format=f5.2
      V328      LABEL="W-O MONEY Y"                                      format=f6.
      V329      LABEL="W-O REAL Y"                                       format=f5.
      V330      LABEL="W-O REAL Y-HSNG"                                  format=f6.
      V331      LABEL="CONTRACTUAL PAYTS"                                format=f5.
      V332      LABEL="TOTAL FIXED EXP"                                  format=f5.
      V333      LABEL="UNCOMMITTED Y"                                    format=f5.
      V334      LABEL="TOTAL FOOD CONS"                                  format=f4.
      V335      LABEL="TOTAL FAMILY WORK"                                format=f5.
      V336      LABEL="FOOD CONS/FOOD STD"                               format=f4.2
      V337      LABEL="HEAD HOURLY EARN"                                 format=f5.2
      V338      LABEL="WIFE HOURLY EARN"                                 format=f5.2
      V339      LABEL="BKT TOT MONEY Y"                                  format=f1.
      V340      LABEL="BKT TOT REAL Y"                                   format=f1.
      V341      LABEL="BKT NET REAL Y"                                   format=f1.
      V342      LABEL="BK NET REAL Y-HSNG"                               format=f1.
      V343      LABEL="BKT W-O MONEY Y"                                  format=f1.
      V344      LABEL="BKT W-O REAL NET Y"                               format=f1.
      V345      LABEL="BKT W-O-HOUSING"                                  format=f1.
      V346      LABEL="BKT CONTRACT PYMTS"                               format=f1.
      V347      LABEL="BK TOTAL FIXED EXP"                               format=f1.
      V348      LABEL="BKT UNCOMMITTED Y"                                format=f1.
      V349      LABEL="BK TOTAL FOOD CONS"                               format=f1.
      V350      LABEL="BK TOT FAMILY WORK"                               format=f1.
      V351      LABEL="FOR BKT 325, SEE V407"                            format=f1.
      V352      LABEL="FOR BKT 326, SEE V408"                            format=f1.
      V353      LABEL="FOR BKT 327, SEE V410"                            format=f1.
      V354      LABEL="BKT FD CONS/FD STD"                               format=f1.
      V355      LABEL="BKT HEAD HRLY EARN"                               format=f1.
      V356      LABEL="BKT WIFE HRLY EARN"                               format=f1.
      V357      LABEL="LAG MARR-1ST CHILD"                               format=f3.
      V358      LABEL="BKT LAG MARR-CHILD"                               format=f1.
      V359      LABEL="RESERVE FUNDS"                                    format=f1.
      V360      LABEL="SEX-MARITAL STATUS"                               format=f1.
      V361      LABEL="REGION NOW"                                       format=f1.
      V362      LABEL="REGION GREW UP"                                   format=f1.
      V363      LABEL="GEO. MOBILITY"                                    format=f1.
      V364      LABEL="AV ACC OF DOLLARY"                                format=f1.
      V365      LABEL="AV ACC OF FINANCES"                               format=f1.
      V366      LABEL="AV ACC OF HOURS"                                  format=f1.
      V367      LABEL="AV ACC NONDOLLARY"                                format=f1.
      V368      LABEL="BKT AGE OF HEAD"                                  format=f1.
      V369      LABEL="BKT AGE OF WIFE"                                  format=f1.
      V370      LABEL="MEAN AGE OF COUPLE"                               format=f2.
      V371      LABEL="BKT AGE OF COUPLE"                                format=f1.
      V372      LABEL="BK COUPLE AGE DIF"                                format=f1.
      V373      LABEL="VALUE/ROOM"                                       format=f5.
      V374      LABEL="BKT VALUE/ROOM"                                   format=f1.
      V375      LABEL="BKT VALUE OF CARS"                                format=f1.
      V376      LABEL="BKT WORD-PICTURE"                                 format=f1.
      V377      LABEL="BKT EARN ELSEWHERE"                               format=f1.
      V378      LABEL="BKT PAY REFUSED"                                  format=f1.
      V379      LABEL="AGE AT MARRIAGE"                                  format=f1.
      V380      LABEL="AGE AT 1ST BIRTH"                                 format=f1.
      V381      LABEL="ACTUAL-REQD ROOMS"                                format=f1.
      V382      LABEL="PERSON PER ROOM"                                  format=f3.1
      V383      LABEL="RACE AND SEX"                                     format=f1.
      V384      LABEL="EMPLOYMENT PROBS"                                 format=f1.
      V385      LABEL="BACKGROUND PROBS"                                 format=f1.
      V386      LABEL="CURRENT HANDICAPS"                                format=f1.
      V387      LABEL="NEIGHBHOOD &  HOUSE"                              format=f1.
      V388      LABEL="SENSE OF EFFICACY"                                format=f1.
      V389      LABEL="TRUST IN OTHERS"                                  format=f1.
      V390      LABEL="ASPIRATIONS EXPRD"                                format=f1.
      V391      LABEL="HORIZON EXPRESSED"                                format=f1.
      V392      LABEL="HORIZON SELF-REPRT"                               format=f1.
      V393      LABEL="CONNECTED TO HELP"                                format=f1.
      V394      LABEL="MONEY EARNING ACTS"                               format=f1.
      V395      LABEL="REAL EARNING ACTS"                                format=f1.
      V396      LABEL="ECONOMIZING"                                      format=f1.
      V397      LABEL="RISK AVOIDANCE"                                   format=f1.
      V398      LABEL="NUMBER OF CHILDREN"                               format=f1.
      V399      LABEL="SSA ECONOMY FX.7"                                 format=f5.2
      V400      LABEL="SSA ECONOMY FX.8"                                 format=f5.2
      V401      LABEL="SSA LOW COST FX.7"                                format=f5.2
      V402      LABEL="SSA LOW COST FX.8"                                format=f5.2
      V403      LABEL="SSA MOD ECON FX.7"                                format=f5.2
      V404      LABEL="SSA MOD ECON FX.8"                                format=f5.2
      V405      LABEL="SSA MOD LO FX.7"                                  format=f5.2
      V406      LABEL="SSA MOD LO FX.8"                                  format=f5.2
      V407      LABEL="BKT MONEY Y/NEEDS"                                format=f1.
      V408      LABEL="BKT NET Y/NEEDS"                                  format=f1.
      V409      LABEL="BKT SSA ECON FX.7"                                format=f1.
      V410      LABEL="BKT NET Y-H/FOOD"                                 format=f1.
      V411      LABEL="BKT PERSONS/ROOM"                                 format=f1.
      V412      LABEL="UNSKILL TEMP LABOR"                               format=f1.
      V413      LABEL="TYPICAL WAGE"                                     format=f1.
      V414      LABEL="UNEMPLOY RATE"                                    format=f1.
      V415      LABEL="PUBLIC WELFARE"                                   format=f1.
      V416      LABEL="SCHOOL EXPENDITURE"                               format=f1.
      V417      LABEL="P CHANGE IN EMPLOY"                               format=f1.
      V418      LABEL="R68 HOUSING QUAL"                                 format=f1.
      V419      LABEL="REV68 EFFICACY"                                   format=f1.
      V420      LABEL="R68 TRUST-HOSTILE"                                format=f1.
      V421      LABEL="WANTED WORK OR HAD"                               format=f1.
      V422      LABEL="NEW JOB DETAILS"                                  format=f1.
      V423      LABEL="R68 AMBITION-ASPIR"                               format=f1.
      V424      LABEL="SAVE> 75 A+R"                                     format=f1.
      V425      LABEL="SAVE> 75 OWN FOOD"                                format=f1.
      V426      LABEL="SAVE> 75 CAR RPR"                                 format=f1.
      V427      LABEL="R68 REAL EARN ACTS"                               format=f1.
      V428      LABEL="SPENT< 150 ALCOH"                                 format=f1.
      V429      LABEL="SPENT< 150 CIGS"                                  format=f1.
      V430      LABEL="FREE HELP>100 HRS"                                format=f1.
      V431      LABEL="NO NEW CAR>65"                                    format=f1.
      V432      LABEL="R68 ECONOMIZING"                                  format=f1.
      V433      LABEL="MED INS OR FREE"                                  format=f1.
      V434      LABEL="R68 RISK AVOIDANCE"                               format=f1.
      V435      LABEL="SQRT W-O MONY"                                    format=f3.
      V436      LABEL="SQRT W-O REAL-V329"                               format=f3.
      V437      LABEL="SQRT W-O HSNG-V330"                               format=f3.
      V438      LABEL="WAGE 2ND JOB BKT"                                 format=f1.
      V439      LABEL="1968 WEIGHT"                                      format=f2.
      V440      LABEL="CENSUS NEEDS STANDARD-1967"                       format=f5.
   ;
   INFILE '[PATH]\FAM1968.txt' LRECL = 771 ; 
   INPUT 
      V1              1 - 1         V2              2 - 6         V3              7 - 10   
      V4             11 - 11        V5             12 - 16        V6             17 - 20   
      V7             21 - 21        V8             22 - 25        V9             26 - 26   
      V10            27 - 30        V11            31 - 31        V12            32 - 35   
      V13            36 - 36        V14            37 - 39        V15            40 - 40   
      V16            41 - 44        V17            45 - 45        V18            46 - 49   
      V19            50 - 50        V20            51 - 54        V21            55 - 55   
      V22            56 - 59        V23            60 - 60        V24            61 - 64   
      V25            65 - 65        V26            66 - 68        V27            69 - 69   
      V28            70 - 73        V29            74 - 74        V30            75 - 75   
      V31            76 - 79        V32            80 - 84        V33            85 - 87   
      V34            88 - 88        V35            89 - 91        V36            92 - 92   
      V37            93 - 96        V38            97 - 97        V39            98 - 100  
      V40           101 - 101       V41           102 - 104       V42           105 - 105  
      V43           106 - 108       V44           109 - 109       V45           110 - 112  
      V46           113 - 113       V47           114 - 117       V48           118 - 118  
      V49           119 - 122       V50           123 - 123       V51           124 - 127  
      V52           128 - 128       V53           129 - 132       V54           133 - 133  
      V55           134 - 137       V56           138 - 138       V57           139 - 142  
      V58           143 - 143       V59           144 - 147       V60           148 - 148  
      V61           149 - 152       V62           153 - 153       V63           154 - 157  
      V64           158 - 158       V65           159 - 162       V66           163 - 163  
      V67           164 - 167       V68           168 - 168       V69           169 - 172  
      V70           173 - 173       V71           174 - 174       V72           175 - 178  
      V73           179 - 182       V74           183 - 187       V75           188 - 192  
      V76           193 - 197       V77           198 - 202       V78           203 - 206  
      V79           207 - 211       V80           212 - 215       V81           216 - 220  
      V82           221 - 224       V83           225 - 229       V84           230 - 234  
      V85           235 - 235       V86           236 - 236       V87           237 - 237  
      V88           238 - 238       V89           239 - 239       V90           240 - 240  
      V91           241 - 241       V92           242 - 244       V93           245 - 246  
      V94           247 - 247       V95           248 - 248       V96           249 - 249  
      V97           250 - 258       V98           259 - 260       V99           261 - 261  
      V100          262 - 264       V101          265 - 265       V102          266 - 266  
      V103          267 - 267       V104          268 - 268       V105          269 - 269  
      V106          270 - 270       V107          271 - 271       V108          272 - 272  
      V109          273 - 273       V110          274 - 274       V111          275 - 275  
      V112          276 - 276       V113          277 - 278       V114          279 - 279  
      V115          280 - 281       V116          282 - 282       V117          283 - 284  
      V118          285 - 286       V119          287 - 287       V120          288 - 288  
      V121          289 - 289       V122          290 - 290       V123          291 - 291  
      V124          292 - 292       V125          293 - 293       V126          294 - 294  
      V127          295 - 295       V128          296 - 296       V129          297 - 297  
      V130          298 - 298       V131          299 - 299       V132          300 - 302  
      V133          303 - 306       V134          307 - 307       V135          308 - 309  
      V136          310 - 310       V137          311 - 311       V138          312 - 313  
      V139          314 - 314       V140          315 - 315       V141          316 - 316  
      V142          317 - 317       V143          318 - 318       V144          319 - 320  
      V145          321 - 324       V146          325 - 325       V147          326 - 326  
      V148          327 - 327       V149          328 - 328       V150          329 - 329  
      V151          330 - 330       V152          331 - 331       V153          332 - 332  
      V154          333 - 333       V155          334 - 334       V156          335 - 335  
      V157          336 - 336       V158          337 - 337       V159          338 - 338  
      V160          339 - 339       V161          340 - 340       V162          341 - 341  
      V163          342 - 342       V164          343 - 343       V165          344 - 344  
      V166          345 - 345       V167          346 - 346       V168          347 - 347  
      V169          348 - 348       V170          349 - 349       V171          350 - 350  
      V172          351 - 351       V173_1        352 - 352       V173_2        353 - 353  
      V174          354 - 354       V175          355 - 355       V176          356 - 356  
      V177_1        357 - 357       V177_2        358 - 358       V178          359 - 359  
      V179          360 - 360       V180          361 - 361       V181          362 - 362  
      V182          363 - 363       V183          364 - 364       V184          365 - 365  
      V185          366 - 366       V186          367 - 367       V187          368 - 368  
      V188          369 - 371       V189          372 - 372       V190          373 - 373  
      V191          374 - 374       V192          375 - 375       V193          376 - 376  
      V194          377 - 377       V195          378 - 379       V196          380 - 380  
      V197          381 - 381       V197_A        382 - 384       V197_B        385 - 387  
      V198          388 - 388       V199          389 - 389       V200          390 - 390  
      V201          391 - 391       V202          392 - 392       V203          393 - 393  
      V204          394 - 394       V205          395 - 395       V206          396 - 396  
      V207          397 - 397       V208          398 - 398       V209          399 - 399  
      V210          400 - 403       V211          404 - 404       V212          405 - 405  
      V213          406 - 406       V214          407 - 407       V215          408 - 408  
      V216          409 - 409       V217          410 - 410       V218          411 - 411  
      V219          412 - 412       V220          413 - 413       V221          414 - 414  
      V222          415 - 415       V223          416 - 416       V224          417 - 417  
      V225          418 - 418       V226          419 - 419       V227          420 - 420  
      V228          421 - 421       V229          422 - 425       V230          426 - 426  
      V231          427 - 427       V232          428 - 428       V233          429 - 429  
      V234          430 - 430       V235          431 - 431       V236          432 - 432  
      V237          433 - 433       V238          434 - 437       V239          438 - 438  
      V240          439 - 440       V241          441 - 441       V242          442 - 442  
      V243          443 - 443       V243_A        444 - 446       V243_B        447 - 449  
      V244          450 - 450       V245          451 - 451       V246          452 - 452  
      V247          453 - 453       V248          454 - 454       V249          455 - 455  
      V250          456 - 456       V251          457 - 457       V252          458 - 458  
      V253          459 - 459       V254          460 - 460       V255          461 - 461  
      V256          462 - 462       V257          463 - 463       V258          464 - 464  
      V259          465 - 465       V260          466 - 466       V261          467 - 467  
      V262          468 - 468       V263          469 - 469       V264          470 - 470  
      V265          471 - 471       V266          472 - 472       V267          473 - 473  
      V268          474 - 474       V269          475 - 475       V270          476 - 476  
      V271          477 - 477       V272          478 - 478       V273          479 - 479  
      V274          480 - 480       V275          481 - 481       V276          482 - 482  
      V277          483 - 483       V278          484 - 484       V279          485 - 485  
      V280          486 - 486       V281          487 - 487       V282_1        488 - 488  
      V282_2        489 - 489       V283          490 - 490       V284          491 - 491  
      V285          492 - 492       V286          493 - 493       V287          494 - 494  
      V288          495 - 495       V289          496 - 496       V290          497 - 497  
      V291          498 - 498       V292          499 - 499       V293          500 - 500  
      V294          501 - 501       V295          502 - 502       V296          503 - 503  
      V297          504 - 504       V298          505 - 505       V299          506 - 506  
      V300          507 - 507       V301          508 - 508       V302          509 - 509  
      V303          510 - 510       V304          511 - 511       V305          512 - 512  
      V306          513 - 513       V307          514 - 514       V308          515 - 515  
      V309          516 - 516       V310          517 - 517       V311          518 - 519  
      V312          520 - 520       V313          521 - 521       V314          522 - 522  
      V315          523 - 523       V316          524 - 524       V317          525 - 525  
      V318          526 - 526       V319          527 - 527       V320          528 - 531  
      V321          532 - 532       V322          533 - 537       V323          538 - 542  
      V324          543 - 547       V325          548 - 552       V326          553 - 557  
      V327          558 - 562       V328          563 - 568       V329          569 - 573  
      V330          574 - 579       V331          580 - 584       V332          585 - 589  
      V333          590 - 594       V334          595 - 598       V335          599 - 603  
      V336          604 - 607       V337          608 - 612       V338          613 - 617  
      V339          618 - 618       V340          619 - 619       V341          620 - 620  
      V342          621 - 621       V343          622 - 622       V344          623 - 623  
      V345          624 - 624       V346          625 - 625       V347          626 - 626  
      V348          627 - 627       V349          628 - 628       V350          629 - 629  
      V351          630 - 630       V352          631 - 631       V353          632 - 632  
      V354          633 - 633       V355          634 - 634       V356          635 - 635  
      V357          636 - 638       V358          639 - 639       V359          640 - 640  
      V360          641 - 641       V361          642 - 642       V362          643 - 643  
      V363          644 - 644       V364          645 - 645       V365          646 - 646  
      V366          647 - 647       V367          648 - 648       V368          649 - 649  
      V369          650 - 650       V370          651 - 652       V371          653 - 653  
      V372          654 - 654       V373          655 - 659       V374          660 - 660  
      V375          661 - 661       V376          662 - 662       V377          663 - 663  
      V378          664 - 664       V379          665 - 665       V380          666 - 666  
      V381          667 - 667       V382          668 - 670       V383          671 - 671  
      V384          672 - 672       V385          673 - 673       V386          674 - 674  
      V387          675 - 675       V388          676 - 676       V389          677 - 677  
      V390          678 - 678       V391          679 - 679       V392          680 - 680  
      V393          681 - 681       V394          682 - 682       V395          683 - 683  
      V396          684 - 684       V397          685 - 685       V398          686 - 686  
      V399          687 - 691       V400          692 - 696       V401          697 - 701  
      V402          702 - 706       V403          707 - 711       V404          712 - 716  
      V405          717 - 721       V406          722 - 726       V407          727 - 727  
      V408          728 - 728       V409          729 - 729       V410          730 - 730  
      V411          731 - 731       V412          732 - 732       V413          733 - 733  
      V414          734 - 734       V415          735 - 735       V416          736 - 736  
      V417          737 - 737       V418          738 - 738       V419          739 - 739  
      V420          740 - 740       V421          741 - 741       V422          742 - 742  
      V423          743 - 743       V424          744 - 744       V425          745 - 745  
      V426          746 - 746       V427          747 - 747       V428          748 - 748  
      V429          749 - 749       V430          750 - 750       V431          751 - 751  
      V432          752 - 752       V433          753 - 753       V434          754 - 754  
      V435          755 - 757       V436          758 - 760       V437          761 - 763  
      V438          764 - 764       V439          765 - 766       V440          767 - 771  
   ;
RUN ;
