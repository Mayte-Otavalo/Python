# Análisis de Desnutrición Infantil y Gestión del Agua en Ecuador

![Python](https://img.shields.io/badge/Python-3.8%2B-blue)
![C++](https://img.shields.io/badge/C++-17-orange)
![Machine Learning](https://img.shields.io/badge/Machine%20Learning-Naive%20Bayes%20%26%20Linear%20Regression-green)

Repositorio del proyecto de análisis de datos para identificar la relación entre el acceso a agua potable y la desnutrición infantil en los cantones ecuatorianos, utilizando modelos de **Naive Bayes** y **Regresión Lineal**.

## 📌 Descripción
Este proyecto analiza datos del INEC (Instituto Nacional de Estadística y Censos de Ecuador) para:
- Identificar cantones con **alto riesgo de desnutrición infantil** debido a la mala gestión del agua.
- Evaluar la **calidad del servicio de agua potable** (días/horas de servicio, tratamiento, análisis microbiológicos).
- Clasificar zonas prioritarias para intervención usando **aprendizaje automático**.

## 📊 Datos
- **Fuente**: [INEC - Estadísticas de Agua Potable y Saneamiento (2023)](https://anda.inec.gob.ec/anda/index.php/catalog/1091/get_microdata).
- **Variables clave**:
  - Días/horas de servicio de agua (urbano/rural).
  - Cumplimiento de la norma INEN 1108 (calidad del agua).
  - Análisis de coliformes fecales y cloro residual.
  - Volumen de agua no tratada distribuida.

## ⚙️ Metodología
1. **Preprocesamiento**:
   - Imputación de valores faltantes (mediana para numéricos, moda para categóricos).
   - Creación de variable objetivo "Desnutrición" basada en umbrales de riesgo.
2. **Modelado**:
   - **Naive Bayes Gaussiano**: Clasificación de cantones en riesgo (precisión: **97.75%**).
   - **Regresión Lineal**: Análisis de correlación entre variables.
3. **Resultados**:
   - 32 cantones identificados con alto riesgo (ej: Guayaquil, Manta, Eloy Alfaro).
   - [Ver matriz de confusión y reporte de clasificación](./docs/results.md).

## 📂 Estructura del Repositorio