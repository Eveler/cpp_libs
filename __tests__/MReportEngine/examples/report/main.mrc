<body>
	<sources>
		<source name="$S_1$">
			<source_type name="SQL"/>
			<source_params driver="QPSQL" host="192.168.91.60" port="5432" database="MFCs"/>
		</source>
	</sources>
	<parameters>
		<parameter name="$P_1$">
			<parameter_type name="InputData"/>
			<parameter_data_type name="DatePeriod"/>
			<parameter_request_parameter value="Period:Random;Daily;Weakly;Monthly;Quarterly;Semiannual;Yearly"/>
		</parameter>
	</parameters>
	<keys>
		<key name="$K_1$">
			<key_type name="SQL"/>
			<key_data_type name="DateTime"/>
			<key_data_source value="SELECT now()"/>
		</key>
		<key name="$K_2$">
			<key_type name="Attachment"/>
			<key_data_source value="Table_1"/>
		</key>
		<key name="$K_3$">
			<key_type name="Attachment"/>
			<key_data_source value="Row_1"/>
		</key>
	</keys>
</body>