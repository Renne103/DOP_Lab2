﻿/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   BubleSort
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */


/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdBubleSort.h"
#include "IEcoCalculatorX.h"
#include "IEcoCalculatorY.h"
#include "IdEcoCalculatorA.h"
#include "IdEcoCalculatorB.h"
#include "IdEcoCalculatorD.h"
#include "IdEcoCalculatorE.h"


#include <time.h>
#include <stdlib.h>



int ECOCDECLMETHOD comparatori(const void * a, const void * b) { 
	int16_t data1 = *(int16_t *)a; 
	int16_t data2 = *(int16_t *)b;
    if (data1 > data2)
		return 1;
	else
		return 0;
}

int ECOCDECLMETHOD comparatord(const void * a, const void * b) { 
    double_t data1 = *(double_t *)a; 
	double_t data2 = *(double_t *)b;
    if (data1 > data2)
		return 1;
	else
		return 0;
}

int ECOCDECLMETHOD comparatorc(const void * a, const void * b) { 
    char data1 = *(char *)a; 
	char data2 = *(char *)b;
    if (data1 > data2)
		return 1;
	else
		return 0;
}



/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    char_t* name = 0;
    char_t* copyName = 0;
    /* Указатель на тестируемый интерфейс */
    IBubleSort* pIBubleSort = 0;
	IEcoCalculatorX* pIX = 0;
	IEcoCalculatorY* pIY = 0;

	int32_t answer1 = 0;

	int16_t arr_int[30] = {99, -2, 76, 96, -68, 36, -26, -21, 34, 52, 59, 85, 6, 75, -70, -92, -77, 70, -65, -3, 53, 100, 94, 84, -53, -95, 89, -20, -31, -10};
	double_t arr_double[30] = {23.3083,70.2118,62.8812,16.4437,83.6103,48.9525,90.3603,70.3762,32.91,82.8918,81.0752,27.7077,97.2646,66.1746,80.7059,96.3442,93.0083,53.4421,28.3258,5.9416,70.6301,94.3844,50.879,90.7564,68.1696,28.374,69.9686,7.4785,35.6852,50.1796};
	char_t arr_char[30] = {'J','S','B','9','b','C','Z','c','Z','K','W','D','f','m','U','3','5','a','e','c','Q','q','Y','t','d','7','p','j','g','f'};
	int16_t size = 30;
	size_t i;

	
	//Переменные для трекинга времени
	double_t time_spent_b = 0.0;
	double_t time_spent_q = 0.0;

	clock_t begin_b;
	clock_t end_b;

	clock_t begin_q;
	clock_t end_q;

	//Переменные для задания количества итераций
	int iter_1000 = 1000;
	int iter_10000 = 10000;
	int iter_100000 = 100000;
	int iter_1000000 = 1000000;



    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem1, (void **)&pISys);
        if (result != 0 && pISys == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#ifdef ECO_LIB
    /* Регистрация статического компонента для Bubble sort */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_BubleSort, (IEcoUnknown*)GetIEcoComponentFactoryPtr_680786EC2FB742F2A3C6C9D4B4ED74BE);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

	/* Регистрация статического компонента A */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoCalculatorA, (IEcoUnknown*)GetIEcoComponentFactoryPtr_4828F6552E4540E78121EBD220DC360E);
    if (result != 0 ) {
        goto Release;
    }


	/* Регистрация статического компонента B */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoCalculatorB, (IEcoUnknown*)GetIEcoComponentFactoryPtr_AE202E543CE54550899603BD70C62565);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

	
	/* Регистрация статического компонента D */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoCalculatorD, (IEcoUnknown*)GetIEcoComponentFactoryPtr_3A8E44677E82475CB4A3719ED8397E61);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

	/* Регистрация статического компонента E */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoCalculatorE, (IEcoUnknown*)GetIEcoComponentFactoryPtr_872FEF1DE3314B87AD44D1E7C232C2F0);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }


#endif
    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Выделение блока памяти */
    name = (char_t *)pIMem->pVTbl->Alloc(pIMem, 10);

    /* Заполнение блока памяти */
    pIMem->pVTbl->Fill(pIMem, name, 'a', 9);


    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_BubleSort, 0, &IID_IBubleSort, (void**) &pIBubleSort);
    if (result != 0 || pIBubleSort == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

	result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorA, 0, &IID_IEcoCalculatorX, (void**) &pIX);
    if (result != 0 || pIX == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

	result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorB, 0, &IID_IEcoCalculatorX, (void**) &pIX);
    if (result != 0 || pIX == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

	result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorD, 0, &IID_IEcoCalculatorY, (void**) &pIY);
    if (result != 0 || pIX == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

	result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorE, 0, &IID_IEcoCalculatorY, (void**) &pIY);
    if (result != 0 || pIX == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }



	pIBubleSort->pVTbl->MyFunction(pIBubleSort, arr_int, size, sizeof(int16_t), comparatori);

	result = pIBubleSort->pVTbl->QueryInterface(pIBubleSort, &IID_IEcoCalculatorX, (void**)&pIX);
	answer1 = pIX->pVTbl->Addition(pIX, 10, 2);
	printf("Variables: 10 2\n");
	printf("The expected result of the addition: 12\n");
	printf("The real result of the addition: %d\n", answer1);

	result = pIBubleSort->pVTbl->QueryInterface(pIBubleSort, &IID_IEcoCalculatorX, (void**)&pIX);
	answer1 = pIX->pVTbl->Subtraction(pIX, 10, 2);
	printf("The expected result of the subtraction: 8\n");
	printf("The real result of the subtraction: %d\n", answer1);
		
	result = pIBubleSort->pVTbl->QueryInterface(pIBubleSort, &IID_IEcoCalculatorY, (void**)&pIY);
	answer1 = pIY->pVTbl->Multiplication(pIY, 10, 2);
	printf("The expected result of the multiplication: 20\n");
	printf("The real result of the multiplication: %d\n", answer1);

	result = pIBubleSort->pVTbl->QueryInterface(pIBubleSort, &IID_IEcoCalculatorY, (void**)&pIY);
	answer1 = pIY->pVTbl->Division(pIY, 10, 2);
	printf("The expected result of the division: 5\n");
	printf("The real result of the division: %d\n", answer1);



    /* Освлбождение блока памяти */
    pIMem->pVTbl->Free(pIMem, name);

Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIBubleSort != 0) {
        pIBubleSort->pVTbl->Release(pIBubleSort);
    }


    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

