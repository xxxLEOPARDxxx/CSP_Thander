
// -------------------------------------------------------------
// Mett: настройки моря
// заготовки на разные типы волнения:
// штиль, легкий бриз, бриз, умеренный бриз, сильный бриз, шторм
// -------------------------------------------------------------

string WhrGetSeaPresetFromWind(float fWind)
{
	string sPreset = "calm";
	if(fWind > 4.0) sPreset = "light_breeze";
	if(fWind > 7.5) sPreset = "breeze";
	if(fWind > 11.0) sPreset = "moderate_breeze";
	if(fWind > 14.5) sPreset = "strong_breeze";
	if(CheckAttribute(&WeatherParams, "Storm") && sti(WeatherParams.Storm) == 1) sPreset = "storm";
	return sPreset;
}

void WhrSetSeaPreset(int iCurWeatherNum, string sPreset)
{
	ref Whr = &Weathers[iCurWeatherNum];
	/* Whr.Sea2.Reflection = 0.8;
    Whr.Sea2.Transparency = 0.3;
    Whr.Sea2.Frenel = 0.3;
    Whr.Sea2.Attenuation = 0.3;
    Whr.Sea2.WaterColor = argb(0, 10, 30, 50);
    Whr.Sea2.SkyColor = argb(0, 255, 255, 255);
    Whr.Sea2.BumpScale = 0.075; //ћ?Ћ »? ¬ќЋЌџ */

	switch(sPreset)
	{
			case "calm": //штиль
				Whr.Sea2.Amp1 = 1.0;//амплитуда 1 волны
				Whr.Sea2.AnimSpeed1 = 1.0; //скорость анимации
				Whr.Sea2.Scale1 = 1.5; //размеры волны
				Whr.Sea2.MoveSpeed1 = "0.0, 0.0, 1.5"; //скорость движения

				Whr.Sea2.Amp2 = 0.7;
				Whr.Sea2.AnimSpeed2 = 2.0;
				Whr.Sea2.Scale2 = 2.0;
				Whr.Sea2.MoveSpeed2 = "-1.5, 0.0, 0.0";

				Whr.Sea2.BumpScale = 0.075; //Ю?О†ї? ђЭОНЯ
				Whr.Sea2.PosShift = 2.0;//остроконечность волн

				Whr.Sea2.FoamK = 0.5;//яркость пены по высоте 0.1 - пена §рка§ с 10 метров 1.0 через метр после начала
				Whr.Sea2.FoamV = 0.9;////высота с которой начинаетс§ пена
				Whr.Sea2.FoamUV = 1.0; //тайлинг пены
				Whr.Sea2.FoamTexDisturb = 0.7;//сдвиг по нормали. х.з. что это надо поюзать. значение от 0.0 до 1.0

				Whr.Sea2.Reflection = 0.8;//0.8;
				Whr.Sea2.Transparency = 0.6;//0.6;
				Whr.Sea2.Frenel = 0.3;//0.6;
				Whr.Sea2.Attenuation = 0.3;//0.2;
				Whr.Sea2.WaterColor = argb(0, 10, 30, 50);
			break;

			case "light_breeze": //легкий бриз
				Whr.Sea2.Amp1 = 1.25;//амплитуда 1 волны
				Whr.Sea2.AnimSpeed1 = 2.0; //скорость анимации
				Whr.Sea2.Scale1 = 1.5; //размеры волны
				Whr.Sea2.MoveSpeed1 = "0.0, 0.0, 2.0"; //скорость движени§

				Whr.Sea2.Amp2 = 0.85;
				Whr.Sea2.AnimSpeed2 = 3.0;
				Whr.Sea2.Scale2 = 3.0;
				Whr.Sea2.MoveSpeed2 = "-2.0, 0.0, 0.0";

				Whr.Sea2.BumpScale = 0.075; //Ю?О†ї? ђЭОНЯ
				Whr.Sea2.PosShift = 1.4;//остроконечность волн

				Whr.Sea2.FoamK = 0.5;//§ркость пены по высоте 0.1 - пена §рка§ с 10 метров 1.0 через метр после начала
				Whr.Sea2.FoamV = 1.1;////высота с которой начинаетс§ пена
				Whr.Sea2.FoamUV = 1.0; //тайлинг пены
				Whr.Sea2.FoamTexDisturb = 0.7;//сдвиг по нормали. х.з. что это надо поюзать. значение от 0.0 до 1.0

				Whr.Sea2.Reflection = 0.8;//0.8;
				Whr.Sea2.Transparency = 0.6;//0.6;
				Whr.Sea2.Frenel = 0.3;//0.6;
				Whr.Sea2.Attenuation = 0.3;//0.2;
				Whr.Sea2.WaterColor = argb(0, 10, 30, 50);
			break;

			case "breeze":	//бриз
				Whr.Sea2.Amp1 = 2.5;//амплитуда 1 волны
				Whr.Sea2.AnimSpeed1 = 3.0; //скорость анимации
				Whr.Sea2.Scale1 = 1.0; //размеры волны
				Whr.Sea2.MoveSpeed1 = "0.0, 0.0, 2.5"; //скорость движени§

				Whr.Sea2.Amp2 = 2.0;
				Whr.Sea2.AnimSpeed2 = 8.0;
				Whr.Sea2.Scale2 = 2.0;
				Whr.Sea2.MoveSpeed2 = "-2.5, 0.0, 0.0";

				Whr.Sea2.BumpScale = 0.075; //Ю?О†ї? ђЭОНЯ
				Whr.Sea2.PosShift = 1.1;//остроконечность волн

				Whr.Sea2.FoamK = 0.35;//§ркость пены по высоте 0.1 - пена §рка§ с 10 метров 1.0 через метр после начала
				Whr.Sea2.FoamV = 2.3;//высота с которой начинаетс§ пена
				Whr.Sea2.FoamUV = 1.0; //тайлинг пены
				Whr.Sea2.FoamTexDisturb = 0.7;//сдвиг по нормали. х.з. что это надо поюзать. значение от 0.0 до 1.0

				Whr.Sea2.Reflection = 0.8;//0.8;
				Whr.Sea2.Transparency = 0.6;//0.6;
				Whr.Sea2.Frenel = 0.3;//0.6;
				Whr.Sea2.Attenuation = 0.3;//0.2;
				Whr.Sea2.WaterColor = argb(0, 10, 30, 50);
			break;

			case "moderate_breeze":	//бриз
				Whr.Sea2.Amp1 = 4.0; //амплитуда 1 волны
				Whr.Sea2.AnimSpeed1 = 2.5; //скорость анимации
				Whr.Sea2.Scale1 = 0.35; //размеры волны
				Whr.Sea2.MoveSpeed1 = "0.0, 0.0, 2.0"; //скорость движени§

				Whr.Sea2.Amp2 = 1.75;
				Whr.Sea2.AnimSpeed2 = 3.5;
				Whr.Sea2.Scale2 = 2.15;
				Whr.Sea2.MoveSpeed2 = "2.0, 0.0, 0.0";

				Whr.Sea2.BumpScale = 0.075; //Ю?О†ї? ђЭОНЯ
				Whr.Sea2.PosShift = 0.95; //остроконечность волн

				Whr.Sea2.FoamK = 0.3;//§ркость пены по высоте 0.1 - пена §рка§ с 10 метров 1.0 через метр после начала
				Whr.Sea2.FoamV = 3.1;//высота с которой начинаетс§ пена
				Whr.Sea2.FoamUV = 1.0; //тайлинг пены
				Whr.Sea2.FoamTexDisturb = 0.7;//сдвиг по нормали. х.з. что это надо поюзать. значение от 0.0 до 1.0

				Whr.Sea2.Reflection = 0.8;//0.8;
				Whr.Sea2.Transparency = 0.6;//0.6;
				Whr.Sea2.Frenel = 0.3;//0.6;
				Whr.Sea2.Attenuation = 0.3;//0.2;
				Whr.Sea2.WaterColor = argb(0, 10, 30, 50);
			break;

			case "strong_breeze"://ветрено
				Whr.Sea2.Amp1 = 6.0; //амплитуда 1 волны
				Whr.Sea2.AnimSpeed1 = 3.0; //скорость анимации
				Whr.Sea2.Scale1 = 0.3; //размеры волны
				Whr.Sea2.MoveSpeed1 = "0.0, 0.0, 3.0"; //скорость движени§

				Whr.Sea2.Amp2 = 1.5;
				Whr.Sea2.AnimSpeed2 = 6.0;
				Whr.Sea2.Scale2 = 2.5;
				Whr.Sea2.MoveSpeed2 = "-3.0, 0.0, 0.0";

				Whr.Sea2.BumpScale = 0.075; //Ю?О†ї? ђЭОНЯ
				Whr.Sea2.PosShift = 0.8; //остроконечность волн

				Whr.Sea2.FoamK = 0.25;//§ркость пены по высоте 0.1 - пена §рка§ с 10 метров 1.0 через метр после начала
				Whr.Sea2.FoamV = 4.2;//высота с которой начинаетс§ пена
				Whr.Sea2.FoamUV = 1.0; //тайлинг пены
				Whr.Sea2.FoamTexDisturb = 0.7;//сдвиг по нормали. х.з. что это надо поюзать. значение от 0.0 до 1.0

				Whr.Sea2.Reflection = 0.8;//0.8;
				Whr.Sea2.Transparency = 0.6;//0.6;
				Whr.Sea2.Frenel = 0.3;//0.6;
				Whr.Sea2.Attenuation = 0.3;//0.2;
				Whr.Sea2.WaterColor = argb(0, 10, 30, 50);
			break;

			case "storm"://шторм
				Whr.Sea2.Amp1 = 37.0; //амплитуда 1 волны
				Whr.Sea2.AnimSpeed1 = 2.0; //скорость анимации
				Whr.Sea2.Scale1 = 0.11; //размеры волны
				Whr.Sea2.MoveSpeed1 = "0.0, 0.0, 10.0"; //скорость движени§

				Whr.Sea2.Amp2 = 2.0;
				Whr.Sea2.AnimSpeed2 = 4.0;
				Whr.Sea2.Scale2 = 2.0;
				Whr.Sea2.MoveSpeed2 = "-4.0, 0.0, 0.0";

				Whr.Sea2.BumpScale = 0.05; //Ю?О†ї? ђЭОНЯ
				Whr.Sea2.PosShift = 1.25; //остроконечность волн

				Whr.Sea2.FoamK = 0.05;//§ркость пены по высоте 0.1 - пена §рка§ с 10 метров 1.0 через метр после начала
				Whr.Sea2.FoamV = 20.0;//высота с которой начинаетс§ пена
				Whr.Sea2.FoamUV = 0.75; //тайлинг пены
				Whr.Sea2.FoamTexDisturb = 0.7;//сдвиг по нормали. х.з. что это надо поюзать. значение от 0.0 до 1.0

				Whr.Sea2.Reflection = 0.4;
				Whr.Sea2.Transparency = 0.2;
				Whr.Sea2.Frenel = 0.4;
				Whr.Sea2.Attenuation = 0.3;
				Whr.Sea2.WaterColor = argb(0, 65, 80, 85);
			break;
	}
	Log_TestInfo("WhrSetSeaPreset: выбран пресет " + sPreset);
}

