# Capstone Project Proposal

Muyuan Zhang

## Project Description and Final Deliverables

*This project is developed for Utah Nanofab cleanroom.*

This is a project using data science tools and web scraping skills to fix several security issues for the cleanroom.

* Leverage the HSC database to send emails when certain events occur. For example, if a user has a run scheduled, they need to have a corresponding data entry log. If they fail to enter run data, the tool owner will be notified, and an email will be sent to the user to inform them that they can be disqualified from the tool because of the violation.
* Running the Denton 635 and not checking out precious metals is also a concern. Build a script to parse recipe names from CSV files and email notifications if a recipe with precious metal is used (Au, Pt, Ag, etc.). Cross-reference the recipe and the run data to filter the users that failed to check out.
* Monitor run data for specific conditions and send the tool owner emails. For example, on the e-beam SJ20, if a user enters run data with a base pressure above 3.0E-6, flag it and send an email.
* Build and maintain an Android application to visualize and display the data above. Add features to allow cleanroom staff to submit comments and collaborate on task lists.

## Project Milestones

* Tidy and analyze the raw datasets by August 1st.
* Develop a Python script to cross-reference datasets and generate email notifications by September 1st.
* Develop a JavaScript / TypeScript script to automatically download run data and reservation datasets from Nanofab cleanroom websites by October 1st.
* Develop an Android application to visualize and display the data by December 1st.

## Proposed Mentor

This project will be enrolled in CS 6800.

## Skills and Tools

* Database query: SQL
* Data tidying: Python
* Getting data and web scraping: JavaScript / TypeScript, Python
* Application development: Android, XML, Java

## Risks and Concerns

* Multiple databases of different design patterns will be cross-referenced. Lack of description of columns, huge efforts are required to figure out the meaning of each column, and data tidying will be complicated.
* Access to the original database is restricted and can only be downloaded via websites. A script for web scraping and imitation of human actions is required instead of simple SQL queries.
* The run data and order data are not open to the public for security concerns. Therefore, the application should be designed very carefully to avoid abuse or attacks.