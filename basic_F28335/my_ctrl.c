/*
 * my_ctrl.h
 *
 *  Created on: 20 de fev de 2018
 *      Author: BARBARA
 */

#include "my_ctrl.h"

// Variáveis globais, acessiveis a todos os includes atravez do extern
volatile Uint32 dt = 0;

// Para freq. de 50 kHz -> 834 pontos
//volatile float sinal_modulante[837] = {0.000000, 0.007540, 0.015079, 0.022618, 0.030155, 0.037690, 0.045224, 0.052754, 0.060282, 0.067806, 0.075327, 0.082843, 0.090354, 0.097861, 0.105362, 0.112856, 0.120345, 0.127826, 0.135301, 0.142767, 0.150226, 0.157676, 0.165116, 0.172548, 0.179970, 0.187381, 0.194782, 0.202172, 0.209550, 0.216917, 0.224271, 0.231612, 0.238940, 0.246255, 0.253555, 0.260842, 0.268113, 0.275369, 0.282609, 0.289834, 0.297042, 0.304233, 0.311406, 0.318562, 0.325700, 0.332820, 0.339920, 0.347001, 0.354063, 0.361104, 0.368125, 0.375124, 0.382103, 0.389060, 0.395994, 0.402906, 0.409796, 0.416662, 0.423504, 0.430322, 0.437116, 0.443885, 0.450628, 0.457346, 0.464038, 0.470704, 0.477343, 0.483955, 0.490539, 0.497095, 0.503623, 0.510123, 0.516593, 0.523034, 0.529446, 0.535827, 0.542178, 0.548498, 0.554786, 0.561044, 0.567269, 0.573462, 0.579623, 0.585750, 0.591844, 0.597905, 0.603932, 0.609924, 0.615882, 0.621804, 0.627691, 0.633543, 0.639358, 0.645138, 0.650880, 0.656586, 0.662254, 0.667885, 0.673477, 0.679031, 0.684547, 0.690024, 0.695461, 0.700859, 0.706218, 0.711536, 0.716813, 0.722050, 0.727246, 0.732400, 0.737513, 0.742584, 0.747613, 0.752599, 0.757542, 0.762443, 0.767299, 0.772113, 0.776882, 0.781608, 0.786288, 0.790925, 0.795516, 0.800062, 0.804562, 0.809017, 0.813426, 0.817788, 0.822104, 0.826374, 0.830596, 0.834771, 0.838899, 0.842979, 0.847011, 0.850994, 0.854930, 0.858817, 0.862655, 0.866444, 0.870184, 0.873874, 0.877515, 0.881105, 0.884646, 0.888136, 0.891576, 0.894966, 0.898304, 0.901591, 0.904827, 0.908012, 0.911145, 0.914226, 0.917255, 0.920232, 0.923157, 0.926029, 0.928848, 0.931615, 0.934329, 0.936990, 0.939597, 0.942151, 0.944652, 0.947098, 0.949491, 0.951830, 0.954115, 0.956346, 0.958522, 0.960644, 0.962711, 0.964723, 0.966681, 0.968583, 0.970431, 0.972223, 0.973960, 0.975642, 0.977268, 0.978839, 0.980354, 0.981813, 0.983217, 0.984564, 0.985856, 0.987092, 0.988271, 0.989394, 0.990461, 0.991472, 0.992427, 0.993325, 0.994166, 0.994951, 0.995679, 0.996351, 0.996966, 0.997525, 0.998027, 0.998472, 0.998860, 0.999192, 0.999466, 0.999684, 0.999845, 0.999949, 0.999997, 0.999987, 0.999921, 0.999798, 0.999618, 0.999381, 0.999087, 0.998737, 0.998330, 0.997866, 0.997345, 0.996768, 0.996134, 0.995443, 0.994696, 0.993892, 0.993031, 0.992115, 0.991142, 0.990112, 0.989026, 0.987884, 0.986686, 0.985432, 0.984121, 0.982755, 0.981333, 0.979855, 0.978321, 0.976732, 0.975087, 0.973387, 0.971632, 0.969821, 0.967955, 0.966034, 0.964058, 0.962028, 0.959942, 0.957802, 0.955608, 0.953359, 0.951057, 0.948700, 0.946289, 0.943824, 0.941306, 0.938734, 0.936109, 0.933430, 0.930699, 0.927914, 0.925077, 0.922187, 0.919245, 0.916251, 0.913204, 0.910106, 0.906956, 0.903754, 0.900501, 0.897197, 0.893841, 0.890435, 0.886979, 0.883471, 0.879914, 0.876307, 0.872649, 0.868943, 0.865186, 0.861381, 0.857527, 0.853624, 0.849672, 0.845672, 0.841624, 0.837528, 0.833385, 0.829194, 0.824956, 0.820671, 0.816339, 0.811961, 0.807537, 0.803067, 0.798551, 0.793990, 0.789384, 0.784733, 0.780037, 0.775297, 0.770513, 0.765685, 0.760814, 0.755899, 0.750942, 0.745941, 0.740898, 0.735813, 0.730687, 0.725519, 0.720309, 0.715059, 0.709767, 0.704436, 0.699065, 0.693653, 0.688203, 0.682713, 0.677184, 0.671617, 0.666012, 0.660369, 0.654688, 0.648970, 0.643215, 0.637424, 0.631596, 0.625733, 0.619834, 0.613900, 0.607930, 0.601927, 0.595889, 0.589817, 0.583711, 0.577573, 0.571401, 0.565197, 0.558961, 0.552694, 0.546394, 0.540064, 0.533703, 0.527312, 0.520890, 0.514440, 0.507959, 0.501450, 0.494913, 0.488347, 0.481754, 0.475133, 0.468485, 0.461811, 0.455110, 0.448383, 0.441631, 0.434854, 0.428052, 0.421226, 0.414376, 0.407502, 0.400605, 0.393685, 0.386743, 0.379779, 0.372793, 0.365787, 0.358759, 0.351711, 0.344643, 0.337555, 0.330449, 0.323323, 0.316179, 0.309017, 0.301837, 0.294641, 0.287427, 0.280198, 0.272952, 0.265691, 0.258414, 0.251123, 0.243818, 0.236499, 0.229166, 0.221821, 0.214463, 0.207092, 0.199710, 0.192316, 0.184912, 0.177497, 0.170072, 0.162637, 0.155193, 0.147740, 0.140279, 0.132810, 0.125333, 0.117849, 0.110359, 0.102862, 0.095359, 0.087851, 0.080338, 0.072820, 0.065299, 0.057773, 0.050244, 0.042713, 0.035179, 0.027642, 0.020105, 0.012566, 0.005027, 0.002513, 0.010053, 0.017592, 0.025130, 0.032667, 0.040202, 0.047734, 0.055264, 0.062791, 0.070314, 0.077833, 0.085347, 0.092857, 0.100362, 0.107861, 0.115353, 0.122839, 0.130319, 0.137790, 0.145254, 0.152710, 0.160157, 0.167595, 0.175023, 0.182441, 0.189849, 0.197247, 0.204633, 0.212007, 0.219369, 0.226719, 0.234056, 0.241380, 0.248690, 0.255986, 0.263267, 0.270533, 0.277784, 0.285019, 0.292238, 0.299440, 0.306626, 0.313794, 0.320944, 0.328075, 0.335188, 0.342283, 0.349357, 0.356412, 0.363446, 0.370460, 0.377453, 0.384424, 0.391374, 0.398301, 0.405205, 0.412087, 0.418945, 0.425779, 0.432589, 0.439375, 0.446135, 0.452870, 0.459580, 0.466263, 0.472920, 0.479550, 0.486152, 0.492727, 0.499274, 0.505793, 0.512283, 0.518743, 0.525175, 0.531576, 0.537947, 0.544288, 0.550597, 0.556876, 0.563122, 0.569337, 0.575519, 0.581669, 0.587785, 0.593868, 0.599918, 0.605933, 0.611914, 0.617860, 0.623770, 0.629646, 0.635485, 0.641289, 0.647056, 0.652786, 0.658479, 0.664135, 0.669753, 0.675333, 0.680874, 0.686377, 0.691841, 0.697265, 0.702650, 0.707995, 0.713299, 0.718563, 0.723787, 0.728969, 0.734109, 0.739208, 0.744265, 0.749279, 0.754251, 0.759180, 0.764066, 0.768909, 0.773708, 0.778462, 0.783173, 0.787839, 0.792460, 0.797036, 0.801567, 0.806052, 0.810492, 0.814885, 0.819232, 0.823533, 0.827786, 0.831993, 0.836152, 0.840264, 0.844328, 0.848344, 0.852312, 0.856231, 0.860102, 0.863923, 0.867696, 0.871419, 0.875093, 0.878717, 0.882291, 0.885815, 0.889289, 0.892712, 0.896084, 0.899405, 0.902675, 0.905894, 0.909062, 0.912177, 0.915241, 0.918253, 0.921213, 0.924120, 0.926974, 0.929776, 0.932526, 0.935222, 0.937865, 0.940454, 0.942991, 0.945473, 0.947902, 0.950277, 0.952598, 0.954865, 0.957077, 0.959235, 0.961339, 0.963388, 0.965382, 0.967321, 0.969205, 0.971034, 0.972808, 0.974527, 0.976190, 0.977798, 0.979350, 0.980847, 0.982287, 0.983672, 0.985001, 0.986274, 0.987491, 0.988652, 0.989756, 0.990805, 0.991797, 0.992732, 0.993611, 0.994434, 0.995200, 0.995910, 0.996563, 0.997159, 0.997699, 0.998181, 0.998608, 0.998977, 0.999289, 0.999545, 0.999744, 0.999886, 0.999972, 1.000000, 0.999972, 0.999886, 0.999744, 0.999545, 0.999289, 0.998977, 0.998608, 0.998181, 0.997699, 0.997159, 0.996563, 0.995910, 0.995200, 0.994434, 0.993611, 0.992732, 0.991797, 0.990805, 0.989756, 0.988652, 0.987491, 0.986274, 0.985001, 0.983672, 0.982287, 0.980847, 0.979350, 0.977798, 0.976190, 0.974527, 0.972808, 0.971034, 0.969205, 0.967321, 0.965382, 0.963388, 0.961339, 0.959235, 0.957077, 0.954865, 0.952598, 0.950277, 0.947902, 0.945473, 0.942991, 0.940454, 0.937865, 0.935222, 0.932526, 0.929776, 0.926974, 0.924120, 0.921213, 0.918253, 0.915241, 0.912177, 0.909062, 0.905894, 0.902675, 0.899405, 0.896084, 0.892712, 0.889289, 0.885815, 0.882291, 0.878717, 0.875093, 0.871419, 0.867696, 0.863923, 0.860102, 0.856231, 0.852312, 0.848344, 0.844328, 0.840264, 0.836152, 0.831993, 0.827786, 0.823533, 0.819232, 0.814885, 0.810492, 0.806052, 0.801567, 0.797036, 0.792460, 0.787839, 0.783173, 0.778462, 0.773708, 0.768909, 0.764066, 0.759180, 0.754251, 0.749279, 0.744265, 0.739208, 0.734109, 0.728969, 0.723787, 0.718563, 0.713299, 0.707995, 0.702650, 0.697265, 0.691841, 0.686377, 0.680874, 0.675333, 0.669753, 0.664135, 0.658479, 0.652786, 0.647056, 0.641289, 0.635485, 0.629646, 0.623770, 0.617860, 0.611914, 0.605933, 0.599918, 0.593868, 0.587785, 0.581669, 0.575519, 0.569337, 0.563122, 0.556876, 0.550597, 0.544288, 0.537947, 0.531576, 0.525175, 0.518743, 0.512283, 0.505793, 0.499274, 0.492727, 0.486152, 0.479550, 0.472920, 0.466263, 0.459580, 0.452870, 0.446135, 0.439375, 0.432589, 0.425779, 0.418945, 0.412087, 0.405205, 0.398301, 0.391374, 0.384424, 0.377453, 0.370460, 0.363446, 0.356412, 0.349357, 0.342283, 0.335188, 0.328075, 0.320944, 0.313794, 0.306626, 0.299440, 0.292238, 0.285019, 0.277784, 0.270533, 0.263267, 0.255986, 0.248690, 0.241380, 0.234056, 0.226719, 0.219369, 0.212007, 0.204633, 0.197247, 0.189849, 0.182441, 0.175023, 0.167595, 0.160157, 0.152710, 0.145254, 0.137790, 0.130319, 0.122839, 0.115353, 0.107861, 0.100362, 0.092857, 0.085347, 0.077833, 0.070314, 0.062791, 0.055264, 0.047734, 0.040202, 0.032667, 0.025130, 0.017592, 0.010053, 0.002513, 0.0, 0.0, 0.0};

// Para freq. de 25 kHz -> 417 pontos
volatile float sinal_modulante[420] = {0.000000, 0.015079, 0.030155, 0.045224, 0.060282, 0.075327, 0.090354, 0.105362, 0.120345, 0.135301, 0.150226, 0.165116, 0.179970, 0.194782, 0.209550, 0.224271, 0.238940, 0.253555, 0.268113, 0.282609, 0.297042, 0.311406, 0.325700, 0.339920, 0.354063, 0.368125, 0.382103, 0.395994, 0.409796, 0.423504, 0.437116, 0.450628, 0.464038, 0.477343, 0.490539, 0.503623, 0.516593, 0.529446, 0.542178, 0.554786, 0.567269, 0.579623, 0.591844, 0.603932, 0.615882, 0.627691, 0.639358, 0.650880, 0.662254, 0.673477, 0.684547, 0.695461, 0.706218, 0.716813, 0.727246, 0.737513, 0.747613, 0.757542, 0.767299, 0.776882, 0.786288, 0.795516, 0.804562, 0.813426, 0.822104, 0.830596, 0.838899, 0.847011, 0.854930, 0.862655, 0.870184, 0.877515, 0.884646, 0.891576, 0.898304, 0.904827, 0.911145, 0.917255, 0.923157, 0.928848, 0.934329, 0.939597, 0.944652, 0.949491, 0.954115, 0.958522, 0.962711, 0.966681, 0.970431, 0.973960, 0.977268, 0.980354, 0.983217, 0.985856, 0.988271, 0.990461, 0.992427, 0.994166, 0.995679, 0.996966, 0.998027, 0.998860, 0.999466, 0.999845, 0.999997, 0.999921, 0.999618, 0.999087, 0.998330, 0.997345, 0.996134, 0.994696, 0.993031, 0.991142, 0.989026, 0.986686, 0.984121, 0.981333, 0.978321, 0.975087, 0.971632, 0.967955, 0.964058, 0.959942, 0.955608, 0.951057, 0.946289, 0.941306, 0.936109, 0.930699, 0.925077, 0.919245, 0.913204, 0.906956, 0.900501, 0.893841, 0.886979, 0.879914, 0.872649, 0.865186, 0.857527, 0.849672, 0.841624, 0.833385, 0.824956, 0.816339, 0.807537, 0.798551, 0.789384, 0.780037, 0.770513, 0.760814, 0.750942, 0.740898, 0.730687, 0.720309, 0.709767, 0.699065, 0.688203, 0.677184, 0.666012, 0.654688, 0.643215, 0.631596, 0.619834, 0.607930, 0.595889, 0.583711, 0.571401, 0.558961, 0.546394, 0.533703, 0.520890, 0.507959, 0.494913, 0.481754, 0.468485, 0.455110, 0.441631, 0.428052, 0.414376, 0.400605, 0.386743, 0.372793, 0.358759, 0.344643, 0.330449, 0.316179, 0.301837, 0.287427, 0.272952, 0.258414, 0.243818, 0.229166, 0.214463, 0.199710, 0.184912, 0.170072, 0.155193, 0.140279, 0.125333, 0.110359, 0.095359, 0.080338, 0.065299, 0.050244, 0.035179, 0.020105, 0.005027, 0.010053, 0.025130, 0.040202, 0.055264, 0.070314, 0.085347, 0.100362, 0.115353, 0.130319, 0.145254, 0.160157, 0.175023, 0.189849, 0.204633, 0.219369, 0.234056, 0.248690, 0.263267, 0.277784, 0.292238, 0.306626, 0.320944, 0.335188, 0.349357, 0.363446, 0.377453, 0.391374, 0.405205, 0.418945, 0.432589, 0.446135, 0.459580, 0.472920, 0.486152, 0.499274, 0.512283, 0.525175, 0.537947, 0.550597, 0.563122, 0.575519, 0.587785, 0.599918, 0.611914, 0.623770, 0.635485, 0.647056, 0.658479, 0.669753, 0.680874, 0.691841, 0.702650, 0.713299, 0.723787, 0.734109, 0.744265, 0.754251, 0.764066, 0.773708, 0.783173, 0.792460, 0.801567, 0.810492, 0.819232, 0.827786, 0.836152, 0.844328, 0.852312, 0.860102, 0.867696, 0.875093, 0.882291, 0.889289, 0.896084, 0.902675, 0.909062, 0.915241, 0.921213, 0.926974, 0.932526, 0.937865, 0.942991, 0.947902, 0.952598, 0.957077, 0.961339, 0.965382, 0.969205, 0.972808, 0.976190, 0.979350, 0.982287, 0.985001, 0.987491, 0.989756, 0.991797, 0.993611, 0.995200, 0.996563, 0.997699, 0.998608, 0.999289, 0.999744, 0.999972, 0.999972, 0.999744, 0.999289, 0.998608, 0.997699, 0.996563, 0.995200, 0.993611, 0.991797, 0.989756, 0.987491, 0.985001, 0.982287, 0.979350, 0.976190, 0.972808, 0.969205, 0.965382, 0.961339, 0.957077, 0.952598, 0.947902, 0.942991, 0.937865, 0.932526, 0.926974, 0.921213, 0.915241, 0.909062, 0.902675, 0.896084, 0.889289, 0.882291, 0.875093, 0.867696, 0.860102, 0.852312, 0.844328, 0.836152, 0.827786, 0.819232, 0.810492, 0.801567, 0.792460, 0.783173, 0.773708, 0.764066, 0.754251, 0.744265, 0.734109, 0.723787, 0.713299, 0.702650, 0.691841, 0.680874, 0.669753, 0.658479, 0.647056, 0.635485, 0.623770, 0.611914, 0.599918, 0.587785, 0.575519, 0.563122, 0.550597, 0.537947, 0.525175, 0.512283, 0.499274, 0.486152, 0.472920, 0.459580, 0.446135, 0.432589, 0.418945, 0.405205, 0.391374, 0.377453, 0.363446, 0.349357, 0.335188, 0.320944, 0.306626, 0.292238, 0.277784, 0.263267, 0.248690, 0.234056, 0.219369, 0.204633, 0.189849, 0.175023, 0.160157, 0.145254, 0.130319, 0.115353, 0.100362, 0.085347, 0.070314, 0.055264, 0.040202, 0.025130, 0.010053, 0,0,0};
volatile Uint32 index_sinal_modulante = 0;
volatile Uint32 index_sinal_modulante2 = 0;
volatile Uint32 Calcula_dt = 1;

volatile float Iin1 = 0.0;
volatile float Iin2 = 0.0;
volatile float Iin3 = 0.0;
volatile float Vout = 0.0;

// Malha de corrente
volatile float Iref = IREF_INIT;        // Começa em 20%
volatile float Iref_max = 2.96650781904;    // Limita em 80%
volatile float Iref_passo = 0.37081347738;  // Passo de 10%
volatile float Erro1 = 0.0;
volatile float Erro2 = 0.0;
volatile float U1 = 0.0;
volatile float U2 = 0.0;
volatile float Erro;
volatile float U;
volatile float Ref;
volatile float Ref1;
volatile float Ref2;
volatile float SF;
volatile float SF1;
volatile float SF2;
volatile float saida = 0.0;


//{
//    botoes();
//    teste_sensores();
//    //sinc();
//
//    DELAY_US(2500);
//}

/**
 * @brief
 */
void ctrl_loop(void)
{

    check_relay();

    if(is_running()){

        check_buttons();

        /*my_scia_send_string("\t I: ");
        my_scia_send_uint16(index_sinal_modulante);
        my_scia_send_string("\t J: ");
        my_scia_send_uint16(index_sinal_modulante2);
        my_scia_send_string("\r\n");*/

        if(interruptionEpwm){
            if(Calcula_dt){
                // Quando index_sinal_modulante chegar ao fim da tabela ele zera
                if(index_sinal_modulante >= 420) index_sinal_modulante = 0;

                Ref=Iref*sinal_modulante[index_sinal_modulante++];

                SF = (0.060788)*Ref2 - (-1.506894)*SF1 - (0.567682)*SF2;
                Ref2=Ref1;
                Ref1=Ref;
                SF2=SF1;
                SF1=SF;

                if(Iin1 < 0) Iin1 = -Iin1;
                Erro=SF-Iin1;

                U = (0.540579)*Erro + (-0.814596)*Erro1 + (0.306877)*Erro2 - (-0.841616)*U1 - (-0.158384)*U2;
                Erro2=Erro1;
                Erro1=Erro;
                U2=U1;
                U1=U;

                Calcula_dt = 0;
            }else{
                Calcula_dt = 1;
            }
            interruptionEpwm = 0;
        }

        dt = U*EPwm1Regs.TBPRD;

    }else{
        dt = 0;
    }

    epwm1_set_dt(dt);
}

/**
 * @brief utiliza o sinal de sincronismo para ligar um led (utilizado para teste)
 */
void test_sinc(void)
{
    /*if(sinc1)   le1_set(); // Acrecentar sinc aqui
    else        led1_clear();

    if(sinc2) led2_set();
    else led2_clear();

    if(sinc3) led3_set();
    else led3_clear();*/
}

/*
 * @brief Usado para identificar se o calculo da corrente está certo
 */
inline void test_sensors(void)
{
    readCurrent1ADC();
    convertCurrent1();
    if(Iin1 > 2.5) led1_set();
    else led1_clear();
    if(Iin1 < -2.5) led2_set();
    else led2_clear();

    readVoltageADC();
    convertVoltage();
    if(Vout > 75) led3_set();
    else led3_clear();
}

/**
 * @brief Alteram o Iref
 * Os botões tem ação apenas 1 vez a cada clique.
 */
inline void check_buttons(void)
{
    static Uint16 b1 = 0, b2 = 0;

    if (!botao1 & !b1){
        if(Iref < Iref_max) Iref = Iref + Iref_passo;
        else Iref = Iref_max;
        b1 = 1;
        led3_set();
    }else if(botao1){
        b1 = 0;
        led2_clear();
    }

    if (!botao2 & !b2){
        if(Iref > 0) Iref = Iref - Iref_passo;
        else Iref = 0;
        b2 = 1;
        led3_set();
    }else if(botao1){
        b2 = 0;
        led3_clear();
    }

}


/**
 * @brief
 *      ALERT: IT FREEZES THE SYSTEM WHILE BUTTON IS BEING PRESSED
 */
inline void check_relay(void)
{
    static Uint32 b3 = 0;

    if (!botao3 & !b3){
        if(is_standby()){ // turn system on
            set_initializing_state();
        }else{                              // turn system off
            set_turningoff_state();
        }
        led2_set();
        b3 = 1;
    }else if(botao3){
        b3 = 0;
        led2_clear();
    }

}