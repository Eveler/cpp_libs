<body>
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
			<key_data_type value="DateTime"/>
			<key_data_source value="SELECT now()"/>
		</key>
		<key name="$K_2$">
			<key_type name="Attachment"/>
			<attachment name="./Table_1/Table_1.mrc"/>
		</key>
		<key name="$K_3$">
			<key_type name="Attachment"/>
			<attachment name="./Row_1/Row_1.mrc"/>
		</key>
	</keys>
</body>