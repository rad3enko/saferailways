#include <SoftwareSerial.h>
#include <TinyGPS++.h>

/** Контстанты */
#define UUID 2
/** Количество узлов в маршруте */
#define SIZE 177

/** Массивы расстояний, широт и долгот узлов маршрута */
const float ARR_DST[SIZE] = {0.0,36.08145276526945,63.343160008836165,90.8405403891639,120.08969383136919,150.17615338186107,169.6868935112395,190.993412414996,216.80867417953968,243.61831051624432,269.5892342673087,295.9186297013876,320.7716402364657,354.12025307958754,372.63465172591674,395.28123947354646,415.7419355749272,437.4651073147132,462.44563260386013,491.56037575265657,520.5321172787487,548.1851338949922,577.2998613925309,607.5213887643823,637.4008931556087,665.4950516671422,697.6728800148951,729.9602814873012,758.2018552100568,793.4539257470105,824.0988802438446,858.3575289671153,893.7288767981248,940.8802386234041,978.8067994886507,1010.6642949126409,1045.5510396552095,1083.3470332856862,1116.2920748300073,1153.850204910018,1185.1287594826192,1214.1124966941563,1251.0110238535833,1280.415509517872,1320.9862831636506,1362.9978622510391,1413.3389794342086,1462.8101417808803,1513.9881154611394,1563.21049105473,1635.3386369807527,1694.1695309639988,1759.4227353261101,1827.1164051735113,1892.369340894787,1950.0988248766682,2013.1789699693,2085.8943337818346,2150.3861797200925,2219.3562006819625,2303.8052131741156,2386.132528801041,2470.059782597445,2571.6093536902285,2673.491998508079,2782.123153010139,2880.7947278521096,2977.30098889294,3089.9204100293064,3199.3490621768556,3333.8367621477832,3452.697996806577,3544.983102723543,3659.388010746414,3782.4825950215095,3898.160349368741,4043.0830276650745,4178.610634752258,4317.906496587947,4482.5782946229165,4623.344532095291,4758.303384303185,4900.05033851498,5054.302621488939,5186.189868261665,5333.671703981006,5472.872568209777,5637.0746222602,5820.447728540948,6010.06891538374,6144.555295900469,6267.0219847156695,6411.326117188736,6538.124635352783,6607.195003739281,6688.328646608983,6759.500443542687,6820.692217312559,6871.796007387034,6923.134664311098,6992.20491338122,7049.695016550654,7103.233860932164,7158.203183236586,7212.609967237412,7275.176711386698,7337.622353064299,7393.9308488637125,7448.595557999788,7495.202448126796,7553.04635869632,7621.060136060751,7694.337893136308,7771.4630311460705,7861.120073298047,7957.9728256881435,8061.173596080183,8163.717785350918,8253.876102696986,8358.859047974185,8447.560258816362,8539.645912471598,8634.954779658121,8724.109096939394,8826.482856432607,8931.65194854781,9023.94464393285,9113.152183845092,9194.196928650126,9255.67085069967,9311.940278251988,9370.870653100877,9402.766998192186,9449.46864445444,9483.309987256387,9537.3551138707,9598.116688698186,9645.10080317113,9707.75500422896,9757.025114731228,9797.348170721238,9843.496668615335,9889.391006277825,9931.954765686834,9975.534735747375,10012.434188207268,10066.161409322256,10107.539302961917,10152.860966051176,10206.900070645028,10254.609943683396,10302.131135506628,10346.849193389662,10394.762520535578,10442.00630903463,10485.867780263527,10529.29823385817,10568.503940246927,10614.127088125451,10647.140128905121,10672.113735118583,10718.045820688865,10761.322057749869,10799.42214573271,10836.584215331533,10879.406390984746,10927.857208944715,10969.561671546526,11004.000473642267,11040.732231991755,11078.843433657248,11110.978374244636,11142.422601722366,11191.095748961729,11226.982621643103,11268.359536615148,11301.344324957998};
const float ARR_LAT[SIZE] = {48.4947,48.494614,48.494543,48.494465,48.494379,48.494293,48.494251,48.494436,48.494657,48.494885,48.495113,48.495334,48.495548,48.495841,48.496005,48.496204,48.496383,48.496575,48.496778,48.497035,48.497292,48.497534,48.497791,48.498055,48.498319,48.498568,48.498853,48.499139,48.499388,48.499702,48.499973,48.500279,48.500593,48.501014,48.501349,48.501634,48.501941,48.502276,48.502568,48.502903,48.503181,48.503438,48.503766,48.50403,48.504393,48.504764,48.505213,48.505648,48.50609,48.506504,48.507103,48.507587,48.508115,48.508685,48.509213,48.509698,48.510211,48.510824,48.511351,48.511922,48.51262,48.513333,48.514074,48.514987,48.515899,48.516869,48.517752,48.518608,48.519606,48.520575,48.521772,48.522827,48.523625,48.524652,48.525735,48.526761,48.528044,48.529241,48.530467,48.53192,48.533174,48.534371,48.535625,48.536993,48.538162,48.539473,48.540698,48.542152,48.543776,48.545457,48.546654,48.547737,48.549019,48.55013,48.550743,48.551469,48.552096,48.552637,48.553093,48.553549,48.554162,48.554674,48.555145,48.555629,48.556113,48.556669,48.557224,48.557723,48.558207,48.55862,48.559133,48.559731,48.560386,48.56107,48.561868,48.562722,48.563634,48.564545,48.565343,48.566283,48.56708,48.567906,48.568761,48.569558,48.570413,48.571295,48.572007,48.572719,48.573289,48.573745,48.574143,48.574571,48.57482,48.57519,48.575475,48.575859,48.576286,48.576585,48.576984,48.577312,48.577554,48.577881,48.578166,48.578451,48.578735,48.578977,48.579305,48.579561,48.579931,48.580415,48.580843,48.58127,48.581668,48.582095,48.582508,48.582893,48.583277,48.583619,48.584017,48.584288,48.584359,48.58416,48.584017,48.583861,48.583726,48.583576,48.583398,48.583213,48.583049,48.582893,48.582701,48.582523,48.582345,48.582046,48.581832,48.581576,48.581369};
const float ARR_LNG[SIZE] = {135.062328,135.0628,135.063154,135.063508,135.063883,135.06427,135.064527,135.064602,135.064709,135.064827,135.064903,135.065031,135.065128,135.065224,135.065267,135.065332,135.065396,135.06545,135.065595,135.06567,135.065734,135.06582,135.065895,135.065992,135.066067,135.066131,135.066206,135.066281,135.066356,135.066421,135.066496,135.066549,135.066625,135.0667,135.066796,135.066839,135.066936,135.067022,135.067097,135.067161,135.067225,135.06729,135.067365,135.067386,135.06744,135.067547,135.067633,135.067773,135.067966,135.068202,135.068577,135.068899,135.069285,135.069607,135.069993,135.070272,135.070637,135.07098,135.071345,135.07171,135.072161,135.072461,135.072676,135.072676,135.072547,135.072375,135.072246,135.072032,135.071774,135.071517,135.071259,135.071002,135.070659,135.070573,135.070229,135.069972,135.069629,135.069285,135.068899,135.06847,135.068212,135.067912,135.067569,135.067225,135.066925,135.066625,135.066238,135.065852,135.065423,135.064994,135.064736,135.064436,135.064135,135.063749,135.063599,135.063492,135.063299,135.063148,135.063063,135.062955,135.062805,135.062698,135.062548,135.062397,135.06229,135.062161,135.062033,135.061904,135.061775,135.061668,135.061539,135.061346,135.061239,135.061067,135.060895,135.060638,135.06038,135.060166,135.059951,135.059822,135.05978,135.059865,135.059951,135.06008,135.060595,135.06111,135.061754,135.062312,135.062998,135.06347,135.063942,135.064414,135.064629,135.064929,135.064768,135.064318,135.063803,135.063352,135.062751,135.062301,135.061893,135.061507,135.061056,135.06067,135.060262,135.059919,135.059383,135.058975,135.058717,135.058653,135.05861,135.058632,135.058546,135.05846,135.05831,135.058181,135.058074,135.057945,135.057795,135.057612,135.05729,135.056743,135.056196,135.055735,135.055273,135.054737,135.054136,135.053643,135.053246,135.052806,135.052377,135.052033,135.051701,135.051218,135.050853,135.050445,135.050124};

/** Настройка пинов коммуникаций */
/** GPS */
static const byte RX_GPS = 10, TX_GPS = 11;
static const uint32_t GPS_BAUD = 9600;
/** Радио */
static const byte RX_RADIO = 4, TX_RADIO = 5;
static const uint32_t RADIO_BAUD = 9600;
/** Модуль управления индикаторами */
static const byte RX_SEGMENTS = 6, TX_SEGMENTS = 7;
static const uint32_t SEGMENTS_BAUD = 9600;

/** Буфер хранения сообщения от передатчика */
char message[32] = ""; 
int messageIterator = 0;

/** Буфер сообщения, передаваемого на модуль управления семисегментными индикаторами */
char segmentsMessage[7] = "";

/** Открываем serial соединения */
SoftwareSerial radio(RX_RADIO, TX_RADIO); // TX не используется
SoftwareSerial gpsSerial(RX_GPS, TX_GPS); // TX не используется
SoftwareSerial segments(RX_SEGMENTS, TX_SEGMENTS); // RX не используется

/** Объект для работы с модулем GPS */
TinyGPSPlus gps;

/** Вспомогательные функции */
int findNearestNode(float lat1, float lng1);
String getUuid(char *msg);
float getLat(char *msg);
float getLng(char *msg);
float getDistanceBetweenNodes(int index1, int index2);

void setup() {
  /** Открываем соединения по радио, GPS, segments каналам */
  radio.begin(RADIO_BAUD);
  gpsSerial.begin(GPS_BAUD);
  segments.begin(SEGMENTS_BAUD);

  /** Время на то, чтобы дошли данные с GPS устройства */
  delay(1000);
}

void loop() {
  while(1) {
    /** Если не ловит спутники или пакет с GPS не проходит валидацию, высвечивает на индикаторах '--G--' */
    if(gps.satellites.value() == 0 || !gps.location.isValid()) {
      segments.print("!--6--#");
      delay(500);
    }
    
    /** Если по радио приходят какие-то данные, начинаем их считывать */
    while(radio.available() > 0){
      char letter = radio.read();

      /** Начало пакета */
      if(letter=='S') messageIterator = 0;

      /** Вносим в буфер пришедший символ, инкреминируем итератор */
      message[messageIterator++] = letter;

      /** Конец пакета, проводим расшифровку */
      if(letter=='E'){ 
        String msg_uuid = getUuid(message);
        float  msg_lat  = getLat(message);
        float  msg_lng  = getLng(message);

        int messageNode = findNearestNode(msg_lat, msg_lng);
        int myNode = findNearestNode(gps.location.lat(), gps.location.lng());

        /** Получаем дистанцию между вычисленными узлами */
        long distBetw = getDistanceBetweenNodes(messageNode, myNode);

        /** Формируем пакет для отправки на модуль управления сегментами */
        char buff[10];
        strcat(segmentsMessage, '!');
        strcat(segmentsMessage, itoa(distBetw, buff, 10));
        strcat(segmentsMessage, '#');

        /** Отправляем на отображение */
        segments.print(segmentsMessage);
      }
    }
  }
}


/** Возвращает ближайший узел с переданным широте и долготе.
 *  Использует массивы координат маршрута.
 *  @param lat1 широта
 *  @param lng1 долгота
 *  @return ближайший узел */
int findNearestNode(float lat1, float lng1){
  int minIndex = 0;
  float minDiff = 999.0;
  for(int i=0; i<SIZE; i++){
    float diff = fabs(lat1 - ARR_LAT[i]) + fabs(lng1 - ARR_LNG[i]);
    if(diff < minDiff){
      minIndex = i;
      minDiff = diff;
    }
  }
  return minIndex;
}

/** @param index1 индекс первого узла
 *  @param index2 индекс второго узла
 *  @return дистанция между узлами */
float getDistanceBetweenNodes(int index1, int index2){
  return fabs(ARR_DST[index2] - ARR_DST[index1]);
}

/** Достает UUID из сообщения */
String getUuid(char *msg){
  return msg[2];
}

/** Достает широту из сообщения */
float getLat(char *msg){
  // 5-12
  float latf = 0;
  char lat1[8];
  for(int i=0; i<8; i++){ lat1[i] = msg[5+i]; }

  latf += 10      * (lat1[0]-'0');
  latf += 1       * (lat1[1]-'0');
  latf += 0.1     * (lat1[3]-'0');
  latf += 0.01    * (lat1[4]-'0');
  latf += 0.001   * (lat1[5]-'0');
  latf += 0.0001  * (lat1[6]-'0');
  latf += 0.00001 * (lat1[7]-'0');
  
  return latf;
}

/** Достает долготу из сообщения */
float getLng(char *msg){
  // 15-22
  char lng1[8];
  float lngf = 0;

  for(int i=0; i<8; i++){ lng1[i] = msg[14+i];}
  
  lngf += 100    * (lng1[0]-'0');
  lngf += 10     * (lng1[1]-'0');
  lngf += 1      * (lng1[2]-'0');
  lngf += 0.1    * (lng1[4]-'0');
  lngf += 0.01   * (lng1[5]-'0');
  lngf += 0.001  * (lng1[6]-'0');
  lngf += 0.0001 * (lng1[7]-'0');
  return lngf;
}