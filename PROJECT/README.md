# Malnutrition Analysis and Water Management in Ecuador

![Python](https://img.shields.io/badge/Python-3.8%2B-blue)
![C++](https://img.shields.io/badge/C++-17-orange)
![Machine Learning](https://img.shields.io/badge/Machine%20Learning-Naive%20Bayes%20%26%20Linear%20Regression-green)

Project repository for data analysis to identify the relationship between access to drinking water and child malnutrition in Ecuadorian cantons, using **Naive Bayes** and **Linear Regression** models.

## 📌 Description
This project analyzes data from INEC (National Institute of Statistics and Census of Ecuador) to:
- Identify cantons with a **high risk of child malnutrition** due to poor water management.
- Evaluate the **quality of drinking water services** (service days/hours, treatment, microbiological analysis).
- Classify priority areas for intervention using **machine learning**.

## 📊 Data
- **Source**: [INEC - Drinking Water and Sanitation Statistics (2023)](https://anda.inec.gob.ec/anda/index.php/catalog/1091/get_microdata)
- **Key variables**:
  - Days/hours of water service (urban/rural).
  - Compliance with INEN 1108 standard (water quality).
  - Fecal coliforms and residual chlorine analysis.
  - Volume of untreated distributed water.

## ⚙️ Methodology
1. **Preprocessing**:
   - Imputation of missing values (median for numerical, mode for categorical).
   - Creation of the target variable "Malnutrition" based on risk thresholds.
2. **Modeling**:
   - **Gaussian Naive Bayes**: Classification of cantons at risk (accuracy: **97.75%**).
   - **Linear Regression**: Correlation analysis between variables.
3. **Results**:
   - 32 cantons identified as high risk (e.g., Guayaquil, Manta, Eloy Alfaro).
   - [See confusion matrix and classification report].

## 📂 Repository Structure
