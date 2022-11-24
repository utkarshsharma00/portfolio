# Research Project
This repository contains the source code for my project "Crop Yield Prediction" which was done in the spring semester of 2019.

This project aims to predict winter wheat yields based on location and weather data. It is inspired by [this](https://github.com/aerialintel/data-science-exercise) exercise and my own project Agro Sense.

## Task
The task is "to try and predict wheat yield for several counties in the United States."

## My approach

As it is, I decided to build a model that is well suited for applications that would ask questions like: "Is location X - which has good coverage of historical weather data - suited for winter wheat and what kind of yield can I expect?"

In its current form, the model is less well suited to answer questions along the lines of: "At location X my weather data so far this season is Y. What kind of yield can I expect at the end of the season?"

My approach to build this model was to characterize each location across the full season. I essentially marginalized over time, engineering aggregated weather-based features for each location. See the 'Feature engineering' section for more details.

*What did I learn along the way?*

It was a great exercise that covered the whole spectrum of a machine-learning project. From data munging over algorithm selection to model tuning and presentation. A good opportunity to get more familiar with the GBT algorithm and the effect of the (numerous) hyper-parameters.

## Executive summary

A gradient-boosted decision tree regressor turned out to be the best performer. The tuned model achieved an R<sup>2</sup> value of ~0.83 with a root mean square error (RMSE) of 5.3 (yield values in the dataset range from 10 to 80). The mean absolute percentage error is ~5%

## Future work

While the performance of the model appears quite good, a close inspection reveals that it has a tendency to under predict at high yield values (>60 observed). There is also some residual overfitting, even after careful tuning.

In future iterations, these issues could be addressed by:

* getting more data,
* engineering additional and/or different features, or
* using ensemble techniques by combining the results of different models.
