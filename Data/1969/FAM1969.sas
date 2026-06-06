
/*************************************************************************
   Label           : 1969 Family Data: Final Release
   Rows            : 4460
   Columns         : 584
   ASCII File Date : December 5, 2013
*************************************************************************/

DATA FAM1969 ; 
   ATTRIB 
      V441      LABEL="RELEASE NUMBER"                                   format=f1.
      V442      LABEL="1969 INT NUMBER"                                  format=f4.
      V443      LABEL="VALUE OF CARS"                                    format=f4.
      V444      LABEL="ACCURACY CAR VALUE"                               format=f1.
      V445      LABEL="SAVED CAR REPAIR"                                 format=f4.
      V446      LABEL="ACCRCY OF SAVD CAR"                               format=f1.
      V447      LABEL="HOURS OF CAR REP"                                 format=f3.
      V448      LABEL="ACCRCY HRS. C.REP."                               format=f1.
      V449      LABEL="HOUSE VALUE"                                      format=f5.
      V450      LABEL="ACCRCY HOUSE VALUE"                               format=f1.
      V451      LABEL="REM MORTG PRIN"                                   format=f5.
      V452      LABEL="ACCRCY REM MORTG PR"                              format=f1.
      V453      LABEL="ANNUAL MORTG PAY"                                 format=f4.
      V454      LABEL="ACCRCY MORTG PAYTS"                               format=f1.
      V455      LABEL="ANNUAL RENT PYTS"                                 format=f4.
      V456      LABEL="ACCRCY RENT PAYTS"                                format=f1.
      V457      LABEL="ANNUAL RENT VAL"                                  format=f4.
      V458      LABEL="ACCRCY RENT VALUE"                                format=f1.
      V459      LABEL="CODE:WORK FOR HOUSE"                              format=f1.
      V460      LABEL="ANNUAL UTIL PYTS"                                 format=f4.
      V461      LABEL="ACCRCY UTIL PYTS"                                 format=f1.
      V462      LABEL="$  SAV ADD + REP"                                 format=f4.
      V463      LABEL="ACCRCY $ SAV ADD+REP"                             format=f1.
      V464      LABEL="HOME PROD HRS (REV)"                              format=f4.
      V465      LABEL="HRS HEAD WORKED"                                  format=f4.
      V466      LABEL="ACCRCY HRS HD WRK"                                format=f1.
      V467      LABEL="HRS HEAD ILL"                                     format=f4.
      V468      LABEL="ACCRCY HRS HD ILL"                                format=f1.
      V469      LABEL="HRS HD UNEMPLD"                                   format=f4.
      V470      LABEL="ACCRCY HRS UNEMPLD"                               format=f1.
      V471      LABEL="$  HEAD TRVL WRK"                                 format=f4.
      V472      LABEL="ACCRCY $  HEAD TRVL"                              format=f1.
      V473      LABEL="HRS HD TRVL WRK"                                  format=f3.
      V474      LABEL="ACCRCY HRS HD TRVL"                               format=f1.
      V475      LABEL="HRS WIFE WORKED"                                  format=f4.
      V476      LABEL="ACCRCY HRS WIFE WRK"                              format=f1.
      V477      LABEL="$  WIFE TRVL WRK"                                 format=f4.
      V478      LABEL="ACCRCY $  WIFE TRVL"                              format=f1.
      V479      LABEL="HRS WF TRVL WRK"                                  format=f3.
      V480      LABEL="ACCRCY HRS WF TRVL"                               format=f1.
      V481      LABEL="HRS HSWRK 1ST."                                   format=f4.
      V482      LABEL="ACCRCY HSWRK 1ST"                                 format=f1.
      V483      LABEL="HRS.HSWK HUSBND"                                  format=f4.
      V484      LABEL="ACCRCY HSWK HUSB"                                 format=f1.
      V485      LABEL="HRS HSWRK OTHRS"                                  format=f4.
      V486      LABEL="ACCRCY HSWRK OTHRS"                               format=f1.
      V487      LABEL="HRS HSWRK NONFU"                                  format=f4.
      V488      LABEL="ACCRCY HRS"                                       format=f1.
      V489      LABEL="$  HSWRK NONFU"                                   format=f4.
      V490      LABEL="ACCRCY $  HSK NONFU"                              format=f1.
      V491      LABEL="TOT NONLEISUR (REV)"                              format=f4.
      V492      LABEL="# MAJOR ADULTS"                                   format=f1.
      V493      LABEL="# IN FAMILY (69)"                                 format=f2.
      V494      LABEL="FU FOOD STANDRD 13:"                              format=f4.
      V495      LABEL="FU NEED STANDRD"                                  format=f5.
      V496      LABEL="$  ANN ALCHL EXP"                                 format=f4.
      V497      LABEL="ACCRCY $  ANN ALCHL"                              format=f1.
      V498      LABEL="$  ANN CIG EXPND"                                 format=f3.
      V499      LABEL="ACCRCY $  ANN CIG"                                format=f1.
      V500      LABEL="$  FOOD USD HOME"                                 format=f4.
      V501      LABEL="ACCRCY $  FOOD HOME"                              format=f1.
      V502      LABEL="$  MEALS WRK/SCH"                                 format=f4.
      V503      LABEL="ACCRCY $  MEALS W/S"                              format=f1.
      V504      LABEL="$  SAVD MEALS W/S"                                format=f4.
      V505      LABEL="ACCRCY $  SAVD MEALS"                             format=f1.
      V506      LABEL="$  EATING OUT"                                    format=f4.
      V507      LABEL="ACCRCY $  EATING OUT"                             format=f1.
      V508      LABEL="$ SAVD GROW FOOD"                                 format=f4.
      V509      LABEL="ACCRCY $  SAVD GR FD"                             format=f1.
      V510      LABEL="$ SAVD FOOD STMP"                                 format=f4.
      V511      LABEL="ACCRCY $ SVD FD STMP"                             format=f1.
      V512      LABEL="$ SVD FREE FOOD"                                  format=f4.
      V513      LABEL="ACCRCY $ SVD FREE FD"                             format=f1.
      V514      LABEL="LABOR INC HEAD"                                   format=f5.
      V515      LABEL="ACCRCY LBR INC HD"                                format=f1.
      V516      LABEL="LABOR INC WIFE"                                   format=f5.
      V517      LABEL="ACCRCY LBR INC WF"                                format=f1.
      V518      LABEL="H+W TAXABLE INC"                                  format=f5.
      V519      LABEL="ACCRCY H+W TXB INC"                               format=f1.
      V520      LABEL="HOURS WRK OTHRS"                                  format=f4.
      V521      LABEL="TAXBL INC OTHRS"                                  format=f5.
      V522      LABEL="ACCRCY TXBL INC OTH"                              format=f1.
      V523      LABEL="ADC,AFDC HEAD+W"                                  format=f4.
      V524      LABEL="ACCRCY ADC INCOME"                                format=f1.
      V525      LABEL="MISC TRANSFERS"                                   format=f5.
      V526      LABEL="ACCRCY MISC TRNSFR"                               format=f1.
      V527      LABEL="TRNSFR INC OTHRS"                                 format=f5.
      V528      LABEL="ACCRCY TR INC OTHR"                               format=f1.
      V529      LABEL="TOTAL FU $  INC"                                  format=f5.
      V530      LABEL="$  CNTRB OUT FU"                                  format=f4.
      V531      LABEL="ACCRCY $  CNTRB OUT"                              format=f1.
      V532      LABEL="FU FED INC TAX"                                   format=f5.
      V533      LABEL="FU COST OF INC"                                   format=f5.
      V534      LABEL="68 IW NUMBER"                                     format=f4.
      V535      LABEL="PSU-HUNDREDS DIGIT"                               format=f1.
      V536      LABEL="PSU ORIG SRC/CPS"                                 format=f3.
      V537      LABEL="STATE NOW"                                        format=f2.
      V538      LABEL="STATE,COUNTY NOW"                                 format=f1.
      V539      LABEL="LRGST PLAC/SMSA PSU"                              format=f1.
      V540      LABEL="PLACE-SRC,FU#-CENS"                               format=f1.
      V541      LABEL="QUALITY OF MATCH"                                 format=f1.
      V542      LABEL="CHANGE IN FU COMP"                                format=f1.
      V543      LABEL="# MOVED INTO FU"                                  format=f1.
      V544      LABEL="REL-HEAD:MOVER IN"                                format=f1.
      V545      LABEL="# MOVED OUT OF FU"                                format=f1.
      V546      LABEL="REL-HEAD:MOVER OUT"                               format=f1.
      V547      LABEL="69 FU COMPOSITION"                                format=f1.
      V548      LABEL="WHETHER TELEPHONE"                                format=f1.
      V549      LABEL="TOTAL # IN FU"                                    format=f2.
      V550      LABEL="# CHILDRN IN FU"                                  format=f2.
      V551      LABEL="IWERS SOC SEC #"                                  format=f9.
      V552      LABEL="IWERS INT #"                                      format=f2.
      V553      LABEL="DATE OF IW      1"                                format=f1.
      V554      LABEL="LNGTH OF IW"                                      format=f3.
      V555      LABEL="ANY CHILD UNDER 25"                               format=f1.
      V556      LABEL="NR CHLDRN IN SCHOOL"                              format=f1.
      V557      LABEL="EDUC EXPT CHILDREN"                               format=f1.
      V558      LABEL="LAST PTA MTG ATTND"                               format=f1.
      V559      LABEL="ANY CHILD STOP SCH"                               format=f1.
      V560      LABEL="HGST GRADE DROP-OUT"                              format=f1.
      V561      LABEL="NR CHLDRN LVNG AWAY"                              format=f1.
      V562      LABEL="AGE OLDST CHILD"                                  format=f2.
      V563      LABEL="AGE 2ND OLDEST"                                   format=f2.
      V564      LABEL="AGE 3RD OLDEST"                                   format=f2.
      V565      LABEL="NR CHLDRN HEAD"                                   format=f2.
      V566      LABEL="NR CHLDRN HD BY25"                                format=f1.
      V567      LABEL="NR SIBLINGS HEAD"                                 format=f1.
      V568      LABEL="HD ANY LIVNG BRTHR"                               format=f1.
      V569      LABEL="AGE OLDST BROTH"                                  format=f1.
      V570      LABEL="ED OLDST LIVNG BROTH"                             format=f1.
      V571      LABEL="OLDST BROTH WELLOFF"                              format=f1.
      V572      LABEL="HD ANY LIVNG SIST"                                format=f1.
      V573      LABEL="AGE OLDST LVNG SIST"                              format=f1.
      V574      LABEL="ED OLDST LVNG SIST"                               format=f1.
      V575      LABEL="OLDST SIST WELL OFF"                              format=f1.
      V576      LABEL="PUBLIC TRANSP AVAIL"                              format=f1.
      V577      LABEL="PUB TRANSP GOOD"                                  format=f1.
      V578      LABEL="OWN A CAR OR TRUCK"                               format=f1.
      V579      LABEL="DIFFIC FR NO CAR"                                 format=f1.
      V580      LABEL="WHAT DIFFIC NO CAR"                               format=f1.
      V581      LABEL="NR CARS OWNED"                                    format=f1.
      V582      LABEL="YR OF NEWST CAR"                                  format=f2.
      V583      LABEL="CONDIT NEWEST CAR"                                format=f1.
      V584      LABEL="ALL CARS INSURED?"                                format=f1.
      V585      LABEL="CAR HAVE SEAT BELTS"                              format=f1.
      V586      LABEL="SEAT BELTS FASTND"                                format=f1.
      V587      LABEL="DID OWN CAR REPAIR"                               format=f1.
      V588      LABEL="KINDS OF CAR REPAIR"                              format=f1.
      V589      LABEL="SAVD CAR REPR BKT"                                format=f1.
      V590      LABEL="TIME ON CAR REPAIR"                               format=f1.
      V591      LABEL="REQUIRED NR ROOMS"                                format=f1.
      V592      LABEL="ACTUAL NR ROOMS"                                  format=f1.
      V593      LABEL="OWN OR RENT?"                                     format=f1.
      V594      LABEL="MORTGAGE?"                                        format=f1.
      V595      LABEL="SECOND MORTGAGE?"                                 format=f1.
      V596      LABEL="WHY FREE HOUSING"                                 format=f1.
      V597      LABEL="WORK DONE ON HOUSE"                               format=f1.
      V598      LABEL="WHAT A+R DONE?"                                   format=f1.
      V599      LABEL="A+R DONE SELF"                                    format=f1.
      V600      LABEL="WHAT A+R DONE SELF"                               format=f1.
      V601      LABEL="NR NEIGHBORS KNOWN"                               format=f1.
      V602      LABEL="RELATIVES NEAR?"                                  format=f1.
      V603      LABEL="MOVED SINCE SPRNG68"                              format=f1.
      V604      LABEL="WHY MOVED"                                        format=f1.
      V605      LABEL="MIGHT MOVE"                                       format=f1.
      V606      LABEL="WHY MIGHT MOVE"                                   format=f1.
      V607      LABEL="MARITAL STATUS"                                   format=f1.
      V608      LABEL="DID WIFE WORK"                                    format=f1.
      V609      LABEL="OCCUPATION-WIFE"                                  format=f1.
      V609_A    LABEL="OCCUPATION OF WIFE         69"                    format=f3.
      V609_B    LABEL="INDUSTRY   OF WIFE         69"                    format=f3.
      V610      LABEL="WEEKS WIFE WRK BKT"                               format=f1.
      V611      LABEL="HRS/WEEK WIFE BKT"                                format=f1.
      V612      LABEL="WIFE UNDER 45"                                    format=f1.
      V613      LABEL="EXPECT CHILDREN?"                                 format=f1.
      V614      LABEL="WHEN EXPCT CHILD"                                 format=f1.
      V615      LABEL="HOW SURE NO CHLDRN"                               format=f1.
      V616      LABEL="WHO DOES HOUSEWORK"                               format=f1.
      V617      LABEL="HRS/WK MAIN HOUSWKR"                              format=f1.
      V618      LABEL="OTHERS DO HOUSEWRK"                               format=f1.
      V619      LABEL="HELP FROM OUTSIDE?"                               format=f1.
      V620      LABEL="PAY FOR HELP?"                                    format=f1.
      V621      LABEL="$ /WK HOME FOOD BKT"                              format=f1.
      V622      LABEL="FOOD DELIVRD ALSO"                                format=f1.
      V623      LABEL="$ /WK DELIVRD FD BKT"                             format=f1.
      V624      LABEL="$ /WK ALCOHOL BKT"                                format=f1.
      V625      LABEL="ALCOH IN FOOD BILL"                               format=f1.
      V626      LABEL="ANY SMOKERS"                                      format=f1.
      V627      LABEL="NR CIGS SMOKED"                                   format=f1.
      V628      LABEL="CIGS IN FOOD BILL"                                format=f1.
      V629      LABEL="MEALS AT WK OR SCH"                               format=f1.
      V630      LABEL="$ /WK MEALS W+S BKT"                              format=f1.
      V631      LABEL="ANY FREE MEALS W+S"                               format=f1.
      V632      LABEL="$ /WK EATING OUT BKT"                             format=f1.
      V633      LABEL="HOME FOOD PRODUCTN"                               format=f1.
      V634      LABEL="FOOD STAMPS?"                                     format=f1.
      V635      LABEL="$ SVD/MO FD STMP BKT"                             format=f1.
      V636      LABEL="PAY/MO FD STMPS BKT"                              format=f1.
      V637      LABEL="OTHER FREE FOOD?"                                 format=f1.
      V638      LABEL="HOW OFTN EAT TGTHR"                               format=f1.
      V639      LABEL="EMPLOYMENT STATUS"                                format=f1.
      V640      LABEL="OCCUPATION OF HEAD"                               format=f1.
      V640_A    LABEL="OCCUPATION OF HEAD         69"                    format=f3.
      V640_B    LABEL="INDUSTRY   OF HEAD         69"                    format=f3.
      V641      LABEL="SELF-EMPLOYED HEAD"                               format=f1.
      V642      LABEL="HOW LONG HAD JOB"                                 format=f1.
      V643      LABEL="HAPPEND PREV JOB"                                 format=f1.
      V644      LABEL="JOB PAY MORE NOW"                                 format=f1.
      V645      LABEL="PRESENT JOB BETTER"                               format=f1.
      V646      LABEL="WHY JOB BETTER"                                   format=f1.
      V647      LABEL="PAY/HR SOUGHT(U)"                                 format=f4.2
      V648      LABEL="TRAINING REQD(U)"                                 format=f1.
      V649      LABEL="HOW FINDING JOB(U)"                               format=f1.
      V650      LABEL="NR PLACES LOOKED(U)"                              format=f1.
      V651      LABEL="HAPPND PREC JOB(U)"                               format=f1.
      V652      LABEL="TOOK VACATION 68(E)"                              format=f1.
      V653      LABEL="WKS VACATION BKT(E)"                              format=f1.
      V654      LABEL="MISS WORK SICK (E)"                               format=f1.
      V655      LABEL="WKS SICK BKT (E)"                                 format=f1.
      V656      LABEL="UNEMPLOYED? (E)"                                  format=f1.
      V657      LABEL="WKS UNEMPLD BKT(E)"                               format=f1.
      V658      LABEL="WEEKS WORK HEAD BKT"                              format=f1.
      V659      LABEL="HOURS/WK WRK HD BKT"                              format=f1.
      V660      LABEL="EXTRA JOBS? (E)"                                  format=f1.
      V661      LABEL="OCCUP XTRA JOB (E)"                               format=f1.
      V662      LABEL="MORE THAN 2 JOBS(E)"                              format=f1.
      V663      LABEL="PAY/HR EXTR WRK"                                  format=f4.2
      V664      LABEL="WEEKS EXTRA JOB (E)"                              format=f1.
      V665      LABEL="HRS/WK EXT JOB (E)"                               format=f1.
      V666      LABEL="MORE WRK AVAILABLE"                               format=f1.
      V667      LABEL="MARGINAL WAGE"                                    format=f4.2
      V668      LABEL="WANTED MORE WORK"                                 format=f1.
      V669      LABEL="COULD WDRKED LESS"                                format=f1.
      V670      LABEL="PREFERD LESS WORK"                                format=f1.
      V671      LABEL="WKS SICK BKT (U)"                                 format=f1.
      V672      LABEL="WKS UNEMPLD BKT(U)"                               format=f1.
      V673      LABEL="DRIVE TO WORK OR?"                                format=f1.
      V674      LABEL="MILES TO WORK"                                    format=f2.
      V675      LABEL="PAY FOR PARKING"                                  format=f1.
      V676      LABEL="LATE GETTNG TO WORK"                              format=f1.
      V677      LABEL="HOW OFTEN LATE"                                   format=f1.
      V678      LABEL="SKIP WORK-NOT SICK"                               format=f1.
      V679      LABEL="HOW OFTEN SKIP WORK"                              format=f1.
      V680      LABEL="MAY GET NEW JOB(E)"                               format=f1.
      V681      LABEL="KIND OF NEW JOB(E)"                               format=f1.
      V682      LABEL="POSSIBLE WAGE(E)"                                 format=f4.2
      V683      LABEL="TRNING NEW JOB?(E)"                               format=f1.
      V684      LABEL="DOING ABT NU JOB(E)"                              format=f1.
      V685      LABEL="#PLACES APPLIED(R)"                               format=f1.
      V686      LABEL="JOBS NOT WORTH IT"                                format=f1.
      V687      LABEL="PAY/HR REJECTED"                                  format=f4.2
      V688      LABEL="WILLING TO MOVE JOB"                              format=f1.
      V689      LABEL="PAY/HR REQD-MOVE"                                 format=f4.2
      V690      LABEL="WHY WONT MOVE JOB"                                format=f1.
      V691      LABEL="CHOOSES WAY WORKS"                                format=f1.
      V692      LABEL="LIKE MORE CHOICE"                                 format=f1.
      V693      LABEL="THINKING WRK FUT(R)"                              format=f1.
      V694      LABEL="WORK DEPENDS ON(R)"                               format=f1.
      V695      LABEL="TOT FARM RECPTS BKT"                              format=f1.
      V696      LABEL="OWN A BUSINESS"                                   format=f1.
      V697      LABEL="BUS INCORPORATED"                                 format=f1.
      V698      LABEL="UNINCORP BUS Y BKT"                               format=f1.
      V699      LABEL="WAGES OF HEAD (BKT)"                              format=f1.
      V700      LABEL="BONUSES ALSO?"                                    format=f1.
      V701      LABEL="PROF PRACTICE Y BKT"                              format=f1.
      V702      LABEL="FARM+ROOMER Y BKT"                                format=f1.
      V703      LABEL="DIV,INT,ETC. BKT"                                 format=f1.
      V704      LABEL="ADC AFDC BKT"                                     format=f1.
      V705      LABEL="OTHER WELFARE BKT"                                format=f1.
      V706      LABEL="SOCIAL SECURITY BKT"                              format=f1.
      V707      LABEL="PENSIONS ETC. BKT"                                format=f1.
      V708      LABEL="UNEMPLOYT COMP,W-C"                               format=f1.
      V709      LABEL="ALIMONY BKT"                                      format=f1.
      V710      LABEL="HELP FROM RELS BKT"                               format=f1.
      V711      LABEL="OTHER INCOME BKT"                                 format=f1.
      V712      LABEL="OTHER HELP?"                                      format=f1.
      V713      LABEL="AMT OTHER HELP BKT"                               format=f1.
      V714      LABEL="WIFE HAD INCOME"                                  format=f1.
      V715      LABEL="KIND OF INC WIFE"                                 format=f1.
      V716      LABEL="WIFE INCOME BKT"                                  format=f1.
      V717      LABEL="# OTHR INC RECEIVES"                              format=f1.
      V718      LABEL="INSURANCE,INHERIT"                                format=f1.
      V719      LABEL="AMT SETTLEMENT BKT"                               format=f1.
      V720      LABEL="Y68 HIGHER OR 67?"                                format=f1.
      V721      LABEL="WHY INC DIFFERENT"                                format=f1.
      V722      LABEL="WHO CAUSD INC CHNG"                               format=f1.
      V723      LABEL="UNUSUAL EXPENSES"                                 format=f1.
      V724      LABEL="WHY EXP UNUSUAL HI"                               format=f1.
      V725      LABEL="Y68 BETTER, OR 67?"                               format=f1.
      V726      LABEL="WHY 68/7 BETTER 1ST"                              format=f1.
      V727      LABEL="WHY 68/7 BETTER 2ND"                              format=f1.
      V728      LABEL="LOT OR LITTL BETTR"                               format=f1.
      V729      LABEL="NXT FEW YRS OUTLOOK"                              format=f1.
      V730      LABEL="1ST REASON OUTLOOK"                               format=f1.
      V731      LABEL="2ND REASON OUTLOOK"                               format=f1.
      V732      LABEL="ANY OUTSIDE DEPS?"                                format=f1.
      V733      LABEL="NR OUTSIDE DEPS"                                  format=f1.
      V734      LABEL="ANY DEP>HALF SUPPT"                               format=f1.
      V735      LABEL="NR DEP >HALF SUPPT"                               format=f1.
      V736      LABEL="WOULD HELP RELATVS"                               format=f1.
      V737      LABEL="ANY SAVINGS"                                      format=f1.
      V738      LABEL="TWO MO INC SAVED?"                                format=f1.
      V739      LABEL="TWO MO INC SVD 5YRS"                              format=f1.
      V740      LABEL="MEDICAL INSURANCE"                                format=f1.
      V741      LABEL="ENTIRE FAMILY INSD"                               format=f1.
      V742      LABEL="FREE MED CARE AVAIL"                              format=f1.
      V743      LABEL="DISAB LIM KIND WRK"                               format=f1.
      V744      LABEL="DISAB LIM AMT WORK"                               format=f1.
      V745      LABEL="HEALTH LIM HSEWRK"                                format=f1.
      V746      LABEL="HOW LONG LIMITED"                                 format=f1.
      V747      LABEL="HEALTH IMPROVING"                                 format=f1.
      V748      LABEL="OTHERS DISABLED?"                                 format=f1.
      V749      LABEL="WHO ELSE DISABLED"                                format=f1.
      V750      LABEL="AGE OF DISABLED"                                  format=f1.
      V751      LABEL="WHY OTHR DISABLED"                                format=f1.
      V752      LABEL="OTHR REQ EXTR CARE"                               format=f1.
      V753      LABEL="WHO REQ EXTRA CARE"                               format=f1.
      V754      LABEL="AGE REQ EXTRA CARE"                               format=f1.
      V755      LABEL="WHY REQ EXTRA CARE"                               format=f1.
      V756      LABEL="WHAT DO SPARE TIME"                               format=f1.
      V757      LABEL="2ND  DO SPARE TIME"                               format=f1.
      V758      LABEL="NR THINGS DONE S-T"                               format=f1.
      V759      LABEL="COURSES OR LESSONS"                               format=f1.
      V760      LABEL="WHAT COURSES"                                     format=f1.
      V761      LABEL="HRS OF TELEVISION"                                format=f1.
      V762      LABEL="HOW OFTN NEWSPAPER"                               format=f1.
      V763      LABEL="HOW OFTEN CHURCH"                                 format=f1.
      V764      LABEL="HOW OFTEN CLUBS"                                  format=f1.
      V765      LABEL="HOW OFTEN BAR+TAVRN"                              format=f1.
      V766      LABEL="UNION MEMBER"                                     format=f1.
      V767      LABEL="AMT UNION DUES BKT"                               format=f1.
      V768      LABEL="PLANS TO MAKE DIFF"                               format=f1.
      V769      LABEL="WHAT PLANS FOR FUT"                               format=f1.
      V770      LABEL="SURE LIFE WORK OUT"                               format=f1.
      V771      LABEL="PLAN OR LIVE DAY-DY"                              format=f1.
      V772      LABEL="CARRY OUT PLANS OR"                               format=f1.
      V773      LABEL="FINISH THINGS OR"                                 format=f1.
      V774      LABEL="LIKE DIFF-CHALLENG"                               format=f1.
      V775      LABEL="RATHR SPND OR SAVE"                               format=f1.
      V776      LABEL="PREFER CHANCE RAISE"                              format=f1.
      V777      LABEL="SATISFIED W SELF"                                 format=f1.
      V778      LABEL="HAVE LIMITATIONS"                                 format=f1.
      V779      LABEL="GET ANGRY EASILY"                                 format=f1.
      V780      LABEL="MATTR OTHRS THINK"                                format=f1.
      V781      LABEL="TRUST MOST OTHERS"                                format=f1.
      V782      LABEL="FIGR WAYS MOR MONEY"                              format=f1.
      V783      LABEL="THINK ABOUT FUTURE"                               format=f1.
      V784      LABEL="AV MAN GETTNG BETTR"                              format=f1.
      V785      LABEL="LOT GOOD DONT DSRV"                               format=f1.
      V786      LABEL="HEAD-GREW UP FARM"                                format=f1.
      V787      LABEL="STATE H GREW UP"                                  format=f2.
      V788      LABEL="ST-CNTY GREW UP"                                  format=f5.
      V789      LABEL="NR REGIONS LDV IN"                                format=f1.
      V790      LABEL="NR STATES H LVD IN"                               format=f1.
      V791      LABEL="SAME HEAD 68-69?"                                 format=f1.
      V792      LABEL="HEADS PARENTS POOR"                               format=f1.
      V793      LABEL="HDS FATHERS EDUC"                                 format=f1.
      V794      LABEL="EDUCATION OF HEAD"                                format=f1.
      V795      LABEL="OTHR TRAINING HEAD"                               format=f1.
      V796      LABEL="HEAD A VETERAN"                                   format=f1.
      V797      LABEL="EVER MOVED FOR JOB"                               format=f1.
      V798      LABEL="EVER REFUSD MOVE"                                 format=f1.
      V799      LABEL="WHO PRESENT"                                      format=f1.
      V800      LABEL="WHO RESPONDENT(REL)"                              format=f1.
      V801      LABEL="RACE"                                             format=f1.
      V802      LABEL="NUMBER OF CALLS"                                  format=f1.
      V803      LABEL="HOW CLEAN DU"                                     format=f1.
      V804      LABEL="READING MTL VISIBLE"                              format=f1.
      V805      LABEL="LANGUAGE PROBLEMS"                                format=f1.
      V806      LABEL="HEAD DISFIGURED"                                  format=f1.
      V807      LABEL="IN CITY OF 5000+"                                 format=f1.
      V808      LABEL="NEAREST SMSA"                                     format=f3.
      V809      LABEL="DIST TO CNTR SMSA"                                format=f1.
      V810      LABEL="TYPE OF STRUCTURE"                                format=f1.
      V811      LABEL="NEIGHBORHOOD-LOWST"                               format=f1.
      V812      LABEL="NEIGHBORHOOD-HGHST"                               format=f1.
      V813      LABEL="DU IN PUB HOUSING"                                format=f1.
      V814      LABEL="INSIDE TOILET"                                    format=f1.
      V815      LABEL="RUNNING WATER"                                    format=f1.
      V816      LABEL="DU NEEDS EXTEN REP"                               format=f1.
      V817      LABEL="GEN OBSERV.-PROBS"                                format=f1.
      V818      LABEL="FLAKEY DATA IN INT"                               format=f1.
      V819_1    LABEL="2 WAYS 68/7 BTR RESP 1"                           format=f1.
      V819_2    LABEL="2 WAYS 68/7 BTR RESP 2"                           format=f1.
      V820_1    LABEL="2 REASONS OUTLK RESP 1"                           format=f1.
      V820_2    LABEL="2 REASONS OUTLK RESP 2"                           format=f1.
      V821_1    LABEL="TWO USES SP TIM RESP 1"                           format=f1.
      V821_2    LABEL="TWO USES SP TIM RESP 2"                           format=f1.
      V822      LABEL="YRLY PROP TAXES"                                  format=f4.
      V823      LABEL="IMPUTED RENT"                                     format=f4.
      V824      LABEL="HOUSE VALUE BKT"                                  format=f1.
      V825      LABEL="LEISURE NET TRAVEL"                               format=f4.
      V826      LABEL="LEISURE COMP 68"                                  format=f4.
      V827      LABEL="BKT TOT FU MON INC"                               format=f1.
      V828      LABEL="BKT LABOR INC HEAD"                               format=f1.
      V829      LABEL="BKT LABOR INC WIFE"                               format=f1.
      V830      LABEL="BKT H+W TAXABLE Y"                                format=f1.
      V831      LABEL="BKT OTHERS TAXBL Y"                               format=f1.
      V832      LABEL="BKT ADC"                                          format=f1.
      V833      LABEL="BKT MISC TRANSFERS"                               format=f1.
      V834      LABEL="BKT OTHRS TRNSF Y"                                format=f1.
      V835      LABEL="MONEY Y/NEEDS"                                    format=f5.2
      V836      LABEL="BKT MONEY Y/NEEDS"                                format=f1.
      V837      LABEL="W-O MONEY"                                        format=f3.
      V838      LABEL="BKT W-O MONEY"                                    format=f1.
      V839      LABEL="FRE HELP FRM OTHRS"                               format=f4.
      V840      LABEL="TOTAL REAL Y"                                     format=f5.
      V841      LABEL="BKT TOTAL REAL Y"                                 format=f1.
      V842      LABEL="REAL NET Y"                                       format=f5.
      V843      LABEL="BKT REAL NET Y"                                   format=f1.
      V844      LABEL="REAL NET Y/NEEDS"                                 format=f5.2
      V845      LABEL="BKT RL NET Y/NEEDS"                               format=f1.
      V846      LABEL="W-O NET REAL"                                     format=f3.
      V847      LABEL="BKT W-O NET REAL"                                 format=f1.
      V848      LABEL="COST OF HOUSING"                                  format=f4.
      V849      LABEL="BKT COST OF HOUSING"                              format=f1.
      V850      LABEL="REAL NET(2)Y"                                     format=f5.
      V851      LABEL="BKT REAL NET(2) Y"                                format=f1.
      V852      LABEL="NET(2) Y/NEEDS"                                   format=f5.2
      V853      LABEL="BKT NET(2) Y/NEEDS"                               format=f1.
      V854      LABEL="W-O NET(2) Y"                                     format=f3.
      V855      LABEL="BKT W-O NET(2)Y"                                  format=f1.
      V856      LABEL="NET Y-HOUSING"                                    format=f5.
      V857      LABEL="BKT NET Y-HOUSING"                                format=f1.
      V858      LABEL="NET Y-HSNG/FD ND"                                 format=f5.2
      V859      LABEL="BKT Y-HSNG/FD ND"                                 format=f1.
      V860      LABEL="W-O NET Y-HSNG"                                   format=f3.
      V861      LABEL="BKT W-O NET Y-HSNG"                               format=f1.
      V862      LABEL="W-O NET(2) Y-HSNG"                                format=f3.
      V863      LABEL="TOTAL FOOD CONS"                                  format=f4.
      V864      LABEL="BKT FOOD CONSMPTN"                                format=f1.
      V865      LABEL="FOOD CONS/FD ND"                                  format=f5.2
      V866      LABEL="BKT FOOD/FD ND"                                   format=f1.
      V867      LABEL="TOTAL FAMILY WORK"                                format=f4.
      V868      LABEL="BKT TOT FAM WORK"                                 format=f1.
      V869      LABEL="FAM WORK INCL TRAV"                               format=f4.
      V870      LABEL="BKT WORK INCL TRAV"                               format=f1.
      V871      LABEL="HEADS HRLY EARN"                                  format=f5.2
      V872      LABEL="BKT HEAD HRLY EARN"                               format=f1.
      V873      LABEL="WIFES HRLY EARN"                                  format=f5.2
      V874      LABEL="BKT WIFE HRLY EARN"                               format=f1.
      V875      LABEL="RESERVE FUNDS"                                    format=f1.
      V876      LABEL="CURRENT REGION"                                   format=f1.
      V877      LABEL="REGION GREW UP"                                   format=f1.
      V878      LABEL="GEOGRAPHCL MOBILITY"                              format=f1.
      V879      LABEL="ACCURACY MONEY INC"                               format=f1.
      V880      LABEL="ACCURACY HOURS"                                   format=f1.
      V881      LABEL="ACCURACY REAL INC"                                format=f1.
      V882      LABEL="# MINOR ASSIGNMTS"                                format=f1.
      V883      LABEL="#MAJOR ASSIGNMTS"                                 format=f2.
      V884      LABEL="VALUE PER ROOM"                                   format=f5.
      V885      LABEL="BKT VALUE/ROOM"                                   format=f1.
      V886      LABEL="BKT CAR VALUE"                                    format=f1.
      V887      LABEL="BKT EARN ELSEWHERE"                               format=f1.
      V888      LABEL="BKT PAY REFUSED"                                  format=f1.
      V889      LABEL="BKT PAY 2ND JOB"                                  format=f1.
      V890      LABEL="BKT MARGINAL WAGE"                                format=f1.
      V891      LABEL="ACTUAL-REQD ROOMS"                                format=f1.
      V892      LABEL="PERSONS PER ROOM"                                 format=f3.1
      V893      LABEL="BKT PERSONS/RM"                                   format=f1.
      V894      LABEL="NUMBER OF ADULTS"                                 format=f2.
      V895      LABEL="HOUSEWORK H+W"                                    format=f4.
      V896      LABEL="HOUSING NBRHD QUAL"                               format=f1.
      V897      LABEL="EFFICACY + PLANNING"                              format=f1.
      V898      LABEL="TRUST OR HOSTILITY"                               format=f1.
      V899      LABEL="SCRAMBLE FOR WORK"                                format=f1.
      V900      LABEL="ASPIRATION AMBITN"                                format=f1.
      V901      LABEL="REAL EARNING ACTS"                                format=f1.
      V902      LABEL="ECONOMIZING"                                      format=f1.
      V903      LABEL="RISK AVOIDANCE"                                   format=f1.
      V904      LABEL="HORIZON PROXIES"                                  format=f1.
      V905      LABEL="CONNECTEDNESS"                                    format=f1.
      V906      LABEL="MONEY EARNING ACTS"                               format=f1.
      V907      LABEL="UNREVISED V24"                                    format=f4.
      V908      LABEL="UNREVISED V51"                                    format=f4.
      V909      LABEL="SPLITOFF INDICATOR"                               format=f1.
      V910      LABEL="CHNG HDS LBR Y"                                   format=f5.
      V911      LABEL="P CHNG HDS LBR Y"                                 format=f4.
      V912      LABEL="BKT CHNG HDS LBR Y"                               format=f1.
      V913      LABEL="BT P CHG HDS LBR Y"                               format=f1.
      V914      LABEL="CHNG WIFES LBR Y"                                 format=f5.
      V915      LABEL="CHNG TAXABLE Y H+W"                               format=f5.
      V916      LABEL="P CHNG TXBL Y H+W"                                format=f4.
      V917      LABEL="CHNG OTHERS TXBL Y"                               format=f5.
      V918      LABEL="CHNG FAM TRNSFRY"                                 format=f5.
      V919      LABEL="CHG FAM MONEY"                                    format=f5.
      V920      LABEL="P CHNG FAM MONEY Y"                               format=f4.
      V921      LABEL="BKT CHNG FAM MON Y"                               format=f1.
      V922      LABEL="BKT P CG FAM MON Y"                               format=f1.
      V923      LABEL="CHNG MONEY Y/NDS"                                 format=f5.2
      V924      LABEL="P CHNG MONEY Y/NDS"                               format=f4.
      V925      LABEL="BKT CHNG MON Y/NDS"                               format=f1.
      V926      LABEL="BT P CG MON Y/NDS"                                format=f1.
      V927      LABEL="CHNG W-O MONEY"                                   format=f3.
      V928      LABEL="P CHNG W-O MONEY"                                 format=f4.
      V929      LABEL="BKT CHNG W-O MONEY"                               format=f1.
      V930      LABEL="BKT P CG W-O MONEY"                               format=f1.
      V931      LABEL="CHNG NON-MONEY Y"                                 format=f5.
      V932      LABEL="CHNG NET REAL Y"                                  format=f5.
      V933      LABEL="PCHNG NET REAL Y"                                 format=f4.
      V934      LABEL="CHNG NET RL Y/NDS"                                format=f5.2
      V935      LABEL="P CG NET RL Y/NDS"                                format=f4.
      V936      LABEL="CHNG W-O NET RL Y"                                format=f3.
      V937      LABEL="P CG W-O NET RL Y"                                format=f4.
      V938      LABEL="CHNG NET RL Y-HSNG"                               format=f5.
      V939      LABEL="P CHG NET RL-HSNG"                                format=f4.
      V940      LABEL="CHNG W-O NET HSNG"                                format=f4.
      V941      LABEL="P CG W-O NET HSNG"                                format=f4.
      V942      LABEL="CG HDS WRK HRS"                                   format=f5.
      V943      LABEL="P CG HDS WRK HRS"                                 format=f4.
      V944      LABEL="BT P CG HDS WK HRS"                               format=f1.
      V945      LABEL="CHG WIFES WRK HRS"                                format=f7.2
      V946      LABEL="CHG HOUSEWRK H+W"                                 format=f5.
      V947      LABEL="CHG HOME PRODN HRS"                               format=f5.
      V948      LABEL="CHG OTHERS WRK HRS"                               format=f5.
      V949      LABEL="CHG TOT FAM HRS"                                  format=f5.
      V950      LABEL="CHG TOT NONLSR"                                   format=f5.
      V951      LABEL="CHG LEISURE/MAJ AD"                               format=f5.
      V952      LABEL="P CHG LEISR/MAJ AD"                               format=f3.
      V953      LABEL="CHNG HDS HRLY EARN"                               format=f5.2
      V954      LABEL="PCG HDS HRLY ERN"                                 format=f4.
      V955      LABEL="BKT P CHG HDS WAGE"                               format=f1.
      V956      LABEL="CHG WIFS HRLY EARN"                               format=f5.2
      V957      LABEL="CHNG FOOD ND STD"                                 format=f5.
      V958      LABEL="P CHNG FOOD ND STD"                               format=f3.
      V959      LABEL="CHG FU NEED STD"                                  format=f5.
      V960      LABEL="CHG FU FOOD CONS"                                 format=f5.
      V961      LABEL="P CHG FU FOOD CONS"                               format=f7.2
      V962      LABEL="CHG FOOD CONS/NDS"                                format=f5.2
      V963      LABEL="PCG FOOD CONS/NDS"                                format=f4.
      V964      LABEL="CHG ALCOHOL EXP"                                  format=f7.2
      V965      LABEL="CHG CIGRT EXP"                                    format=f4.
      V966      LABEL="CHG HORIZN PROXIES"                               format=f1.
      V967      LABEL="CHG CONNECTEDNESS"                                format=f1.
      V968      LABEL="CHG MON EARNG ACTS"                               format=f1.
      V969      LABEL="CHG HSNG NBRHD QUAL"                              format=f1.
      V970      LABEL="CHG EFFICACY+PLNNG"                               format=f1.
      V971      LABEL="CHG TRUST-HOSTILTY"                               format=f1.
      V972      LABEL="CHG ASPIRATN AMBITN"                              format=f1.
      V973      LABEL="CHG RL EARNG ACTS"                                format=f1.
      V974      LABEL="CHG ECONOMIZING"                                  format=f1.
      V975      LABEL="CHG RISK AVOIDANCE"                               format=f1.
      V976      LABEL="CHG NUMBER IN FU"                                 format=f2.
      V977      LABEL="CHG JOB OR OCCUP"                                 format=f1.
      V978      LABEL="CHG EARNERS RCVRS"                                format=f1.
      V979      LABEL="GEOG MOBLTY 1 YEAR"                               format=f1.
      V980      LABEL="MOVED WITHIN COUNTY"                              format=f1.
      V981      LABEL="MOVED BET COUNTIES"                               format=f1.
      V982      LABEL="MOVED BET STATES"                                 format=f1.
      V983      LABEL="MOVED/NOT MOVED"                                  format=f1.
      V984      LABEL="BKT CHG H.WAGE"                                   format=f1.
      V985      LABEL="BKT CHG H HRS"                                    format=f1.
      V986      LABEL="BKT CHG W WAGE"                                   format=f1.
      V987      LABEL="BKT CHG W HRS"                                    format=f1.
      V988      LABEL="BT HEAD 68 OCCUP"                                 format=f1.
      V989      LABEL="CG NT-HSNG/FD ND"                                 format=f6.2
      V990      LABEL="DEC MONEY Y"                                      format=f1.
      V991      LABEL="DEC ORSHAN:MONEY"                                 format=f1.
      V992      LABEL="DEC W-O:MONEY"                                    format=f1.
      V993      LABEL="DEC REAL NET Y"                                   format=f1.
      V994      LABEL="DEC ORSH:REAL NET"                                format=f1.
      V995      LABEL="DEC W-O:REAL NET"                                 format=f1.
      V996      LABEL="DEC REAL NET |-HSNG"                              format=f1.
      V997      LABEL="DEC ORS:REL NET-HSG"                              format=f1.
      V998      LABEL="DEC WO:REL NET-HSG"                               format=f1.
      V999      LABEL="68 DEC MONEY Y"                                   format=f1.
      V1000     LABEL="68 DEC REAL NET Y"                                format=f1.
      V1001     LABEL="68 DEC REL NET Y-HOUSING"                         format=f1.
      V1002     LABEL="68 DEC ORSHANSKY: MONEY"                          format=f1.
      V1003     LABEL="68 DEC ORSH: REAL NET"                            format=f1.
      V1004     LABEL="68 DEC ORSH: REL NET HSG"                         format=f1.
      V1005     LABEL="68 DEC W-O: MONEY"                                format=f1.
      V1006     LABEL="68 DEC W-O: REAL NET"                             format=f1.
      V1007     LABEL="68 DEC W-O: REL NET-HSNG"                         format=f1.
      V1008     LABEL="AGE OF HEAD"                                      format=f2.
      V1009     LABEL="BKT AGE HEAD"                                     format=f1.
      V1010     LABEL="SEX OF HEAD"                                      format=f1.
      V1011     LABEL="AGE OF WIFE"                                      format=f2.
      V1012     LABEL="BKT AGE WIFE"                                     format=f1.
      V1013     LABEL="AGE YNGST CHLD"                                   format=f1.
      V1014     LABEL="1969 FAMILY WEIGHT"                               format=f2.
      V1015     LABEL="HOUSEHOLD ID # 69"                                format=f4.
      V1016     LABEL="FU PRIMACY WITHIN HU"                             format=f1.
      V1017     LABEL="CENSUS NEEDS STANDARD-1968"                       format=f5.
   ;
   INFILE '[PATH]\FAM1969.txt' LRECL = 1079 ; 
   INPUT 
      V441            1 - 1         V442            2 - 5         V443            6 - 9    
      V444           10 - 10        V445           11 - 14        V446           15 - 15   
      V447           16 - 18        V448           19 - 19        V449           20 - 24   
      V450           25 - 25        V451           26 - 30        V452           31 - 31   
      V453           32 - 35        V454           36 - 36        V455           37 - 40   
      V456           41 - 41        V457           42 - 45        V458           46 - 46   
      V459           47 - 47        V460           48 - 51        V461           52 - 52   
      V462           53 - 56        V463           57 - 57        V464           58 - 61   
      V465           62 - 65        V466           66 - 66        V467           67 - 70   
      V468           71 - 71        V469           72 - 75        V470           76 - 76   
      V471           77 - 80        V472           81 - 81        V473           82 - 84   
      V474           85 - 85        V475           86 - 89        V476           90 - 90   
      V477           91 - 94        V478           95 - 95        V479           96 - 98   
      V480           99 - 99        V481          100 - 103       V482          104 - 104  
      V483          105 - 108       V484          109 - 109       V485          110 - 113  
      V486          114 - 114       V487          115 - 118       V488          119 - 119  
      V489          120 - 123       V490          124 - 124       V491          125 - 128  
      V492          129 - 129       V493          130 - 131       V494          132 - 135  
      V495          136 - 140       V496          141 - 144       V497          145 - 145  
      V498          146 - 148       V499          149 - 149       V500          150 - 153  
      V501          154 - 154       V502          155 - 158       V503          159 - 159  
      V504          160 - 163       V505          164 - 164       V506          165 - 168  
      V507          169 - 169       V508          170 - 173       V509          174 - 174  
      V510          175 - 178       V511          179 - 179       V512          180 - 183  
      V513          184 - 184       V514          185 - 189       V515          190 - 190  
      V516          191 - 195       V517          196 - 196       V518          197 - 201  
      V519          202 - 202       V520          203 - 206       V521          207 - 211  
      V522          212 - 212       V523          213 - 216       V524          217 - 217  
      V525          218 - 222       V526          223 - 223       V527          224 - 228  
      V528          229 - 229       V529          230 - 234       V530          235 - 238  
      V531          239 - 239       V532          240 - 244       V533          245 - 249  
      V534          250 - 253       V535          254 - 254       V536          255 - 257  
      V537          258 - 259       V538          260 - 260       V539          261 - 261  
      V540          262 - 262       V541          263 - 263       V542          264 - 264  
      V543          265 - 265       V544          266 - 266       V545          267 - 267  
      V546          268 - 268       V547          269 - 269       V548          270 - 270  
      V549          271 - 272       V550          273 - 274       V551          275 - 283  
      V552          284 - 285       V553          286 - 286       V554          287 - 289  
      V555          290 - 290       V556          291 - 291       V557          292 - 292  
      V558          293 - 293       V559          294 - 294       V560          295 - 295  
      V561          296 - 296       V562          297 - 298       V563          299 - 300  
      V564          301 - 302       V565          303 - 304       V566          305 - 305  
      V567          306 - 306       V568          307 - 307       V569          308 - 308  
      V570          309 - 309       V571          310 - 310       V572          311 - 311  
      V573          312 - 312       V574          313 - 313       V575          314 - 314  
      V576          315 - 315       V577          316 - 316       V578          317 - 317  
      V579          318 - 318       V580          319 - 319       V581          320 - 320  
      V582          321 - 322       V583          323 - 323       V584          324 - 324  
      V585          325 - 325       V586          326 - 326       V587          327 - 327  
      V588          328 - 328       V589          329 - 329       V590          330 - 330  
      V591          331 - 331       V592          332 - 332       V593          333 - 333  
      V594          334 - 334       V595          335 - 335       V596          336 - 336  
      V597          337 - 337       V598          338 - 338       V599          339 - 339  
      V600          340 - 340       V601          341 - 341       V602          342 - 342  
      V603          343 - 343       V604          344 - 344       V605          345 - 345  
      V606          346 - 346       V607          347 - 347       V608          348 - 348  
      V609          349 - 349       V609_A        350 - 352       V609_B        353 - 355  
      V610          356 - 356       V611          357 - 357       V612          358 - 358  
      V613          359 - 359       V614          360 - 360       V615          361 - 361  
      V616          362 - 362       V617          363 - 363       V618          364 - 364  
      V619          365 - 365       V620          366 - 366       V621          367 - 367  
      V622          368 - 368       V623          369 - 369       V624          370 - 370  
      V625          371 - 371       V626          372 - 372       V627          373 - 373  
      V628          374 - 374       V629          375 - 375       V630          376 - 376  
      V631          377 - 377       V632          378 - 378       V633          379 - 379  
      V634          380 - 380       V635          381 - 381       V636          382 - 382  
      V637          383 - 383       V638          384 - 384       V639          385 - 385  
      V640          386 - 386       V640_A        387 - 389       V640_B        390 - 392  
      V641          393 - 393       V642          394 - 394       V643          395 - 395  
      V644          396 - 396       V645          397 - 397       V646          398 - 398  
      V647          399 - 402       V648          403 - 403       V649          404 - 404  
      V650          405 - 405       V651          406 - 406       V652          407 - 407  
      V653          408 - 408       V654          409 - 409       V655          410 - 410  
      V656          411 - 411       V657          412 - 412       V658          413 - 413  
      V659          414 - 414       V660          415 - 415       V661          416 - 416  
      V662          417 - 417       V663          418 - 421       V664          422 - 422  
      V665          423 - 423       V666          424 - 424       V667          425 - 428  
      V668          429 - 429       V669          430 - 430       V670          431 - 431  
      V671          432 - 432       V672          433 - 433       V673          434 - 434  
      V674          435 - 436       V675          437 - 437       V676          438 - 438  
      V677          439 - 439       V678          440 - 440       V679          441 - 441  
      V680          442 - 442       V681          443 - 443       V682          444 - 447  
      V683          448 - 448       V684          449 - 449       V685          450 - 450  
      V686          451 - 451       V687          452 - 455       V688          456 - 456  
      V689          457 - 460       V690          461 - 461       V691          462 - 462  
      V692          463 - 463       V693          464 - 464       V694          465 - 465  
      V695          466 - 466       V696          467 - 467       V697          468 - 468  
      V698          469 - 469       V699          470 - 470       V700          471 - 471  
      V701          472 - 472       V702          473 - 473       V703          474 - 474  
      V704          475 - 475       V705          476 - 476       V706          477 - 477  
      V707          478 - 478       V708          479 - 479       V709          480 - 480  
      V710          481 - 481       V711          482 - 482       V712          483 - 483  
      V713          484 - 484       V714          485 - 485       V715          486 - 486  
      V716          487 - 487       V717          488 - 488       V718          489 - 489  
      V719          490 - 490       V720          491 - 491       V721          492 - 492  
      V722          493 - 493       V723          494 - 494       V724          495 - 495  
      V725          496 - 496       V726          497 - 497       V727          498 - 498  
      V728          499 - 499       V729          500 - 500       V730          501 - 501  
      V731          502 - 502       V732          503 - 503       V733          504 - 504  
      V734          505 - 505       V735          506 - 506       V736          507 - 507  
      V737          508 - 508       V738          509 - 509       V739          510 - 510  
      V740          511 - 511       V741          512 - 512       V742          513 - 513  
      V743          514 - 514       V744          515 - 515       V745          516 - 516  
      V746          517 - 517       V747          518 - 518       V748          519 - 519  
      V749          520 - 520       V750          521 - 521       V751          522 - 522  
      V752          523 - 523       V753          524 - 524       V754          525 - 525  
      V755          526 - 526       V756          527 - 527       V757          528 - 528  
      V758          529 - 529       V759          530 - 530       V760          531 - 531  
      V761          532 - 532       V762          533 - 533       V763          534 - 534  
      V764          535 - 535       V765          536 - 536       V766          537 - 537  
      V767          538 - 538       V768          539 - 539       V769          540 - 540  
      V770          541 - 541       V771          542 - 542       V772          543 - 543  
      V773          544 - 544       V774          545 - 545       V775          546 - 546  
      V776          547 - 547       V777          548 - 548       V778          549 - 549  
      V779          550 - 550       V780          551 - 551       V781          552 - 552  
      V782          553 - 553       V783          554 - 554       V784          555 - 555  
      V785          556 - 556       V786          557 - 557       V787          558 - 559  
      V788          560 - 564       V789          565 - 565       V790          566 - 566  
      V791          567 - 567       V792          568 - 568       V793          569 - 569  
      V794          570 - 570       V795          571 - 571       V796          572 - 572  
      V797          573 - 573       V798          574 - 574       V799          575 - 575  
      V800          576 - 576       V801          577 - 577       V802          578 - 578  
      V803          579 - 579       V804          580 - 580       V805          581 - 581  
      V806          582 - 582       V807          583 - 583       V808          584 - 586  
      V809          587 - 587       V810          588 - 588       V811          589 - 589  
      V812          590 - 590       V813          591 - 591       V814          592 - 592  
      V815          593 - 593       V816          594 - 594       V817          595 - 595  
      V818          596 - 596       V819_1        597 - 597       V819_2        598 - 598  
      V820_1        599 - 599       V820_2        600 - 600       V821_1        601 - 601  
      V821_2        602 - 602       V822          603 - 606       V823          607 - 610  
      V824          611 - 611       V825          612 - 615       V826          616 - 619  
      V827          620 - 620       V828          621 - 621       V829          622 - 622  
      V830          623 - 623       V831          624 - 624       V832          625 - 625  
      V833          626 - 626       V834          627 - 627       V835          628 - 632  
      V836          633 - 633       V837          634 - 636       V838          637 - 637  
      V839          638 - 641       V840          642 - 646       V841          647 - 647  
      V842          648 - 652       V843          653 - 653       V844          654 - 658  
      V845          659 - 659       V846          660 - 662       V847          663 - 663  
      V848          664 - 667       V849          668 - 668       V850          669 - 673  
      V851          674 - 674       V852          675 - 679       V853          680 - 680  
      V854          681 - 683       V855          684 - 684       V856          685 - 689  
      V857          690 - 690       V858          691 - 695       V859          696 - 696  
      V860          697 - 699       V861          700 - 700       V862          701 - 703  
      V863          704 - 707       V864          708 - 708       V865          709 - 713  
      V866          714 - 714       V867          715 - 718       V868          719 - 719  
      V869          720 - 723       V870          724 - 724       V871          725 - 729  
      V872          730 - 730       V873          731 - 735       V874          736 - 736  
      V875          737 - 737       V876          738 - 738       V877          739 - 739  
      V878          740 - 740       V879          741 - 741       V880          742 - 742  
      V881          743 - 743       V882          744 - 744       V883          745 - 746  
      V884          747 - 751       V885          752 - 752       V886          753 - 753  
      V887          754 - 754       V888          755 - 755       V889          756 - 756  
      V890          757 - 757       V891          758 - 758       V892          759 - 761  
      V893          762 - 762       V894          763 - 764       V895          765 - 768  
      V896          769 - 769       V897          770 - 770       V898          771 - 771  
      V899          772 - 772       V900          773 - 773       V901          774 - 774  
      V902          775 - 775       V903          776 - 776       V904          777 - 777  
      V905          778 - 778       V906          779 - 779       V907          780 - 783  
      V908          784 - 787       V909          788 - 788       V910          789 - 793  
      V911          794 - 797       V912          798 - 798       V913          799 - 799  
      V914          800 - 804       V915          805 - 809       V916          810 - 813  
      V917          814 - 818       V918          819 - 823       V919          824 - 828  
      V920          829 - 832       V921          833 - 833       V922          834 - 834  
      V923          835 - 839       V924          840 - 843       V925          844 - 844  
      V926          845 - 845       V927          846 - 848       V928          849 - 852  
      V929          853 - 853       V930          854 - 854       V931          855 - 859  
      V932          860 - 864       V933          865 - 868       V934          869 - 873  
      V935          874 - 877       V936          878 - 880       V937          881 - 884  
      V938          885 - 889       V939          890 - 893       V940          894 - 897  
      V941          898 - 901       V942          902 - 906       V943          907 - 910  
      V944          911 - 911       V945          912 - 918       V946          919 - 923  
      V947          924 - 928       V948          929 - 933       V949          934 - 938  
      V950          939 - 943       V951          944 - 948       V952          949 - 951  
      V953          952 - 956       V954          957 - 960       V955          961 - 961  
      V956          962 - 966       V957          967 - 971       V958          972 - 974  
      V959          975 - 979       V960          980 - 984       V961          985 - 991  
      V962          992 - 996       V963          997 - 1000      V964         1001 - 1007 
      V965         1008 - 1011      V966         1012 - 1012      V967         1013 - 1013 
      V968         1014 - 1014      V969         1015 - 1015      V970         1016 - 1016 
      V971         1017 - 1017      V972         1018 - 1018      V973         1019 - 1019 
      V974         1020 - 1020      V975         1021 - 1021      V976         1022 - 1023 
      V977         1024 - 1024      V978         1025 - 1025      V979         1026 - 1026 
      V980         1027 - 1027      V981         1028 - 1028      V982         1029 - 1029 
      V983         1030 - 1030      V984         1031 - 1031      V985         1032 - 1032 
      V986         1033 - 1033      V987         1034 - 1034      V988         1035 - 1035 
      V989         1036 - 1041      V990         1042 - 1042      V991         1043 - 1043 
      V992         1044 - 1044      V993         1045 - 1045      V994         1046 - 1046 
      V995         1047 - 1047      V996         1048 - 1048      V997         1049 - 1049 
      V998         1050 - 1050      V999         1051 - 1051      V1000        1052 - 1052 
      V1001        1053 - 1053      V1002        1054 - 1054      V1003        1055 - 1055 
      V1004        1056 - 1056      V1005        1057 - 1057      V1006        1058 - 1058 
      V1007        1059 - 1059      V1008        1060 - 1061      V1009        1062 - 1062 
      V1010        1063 - 1063      V1011        1064 - 1065      V1012        1066 - 1066 
      V1013        1067 - 1067      V1014        1068 - 1069      V1015        1070 - 1073 
      V1016        1074 - 1074      V1017        1075 - 1079 
   ;
RUN ;
