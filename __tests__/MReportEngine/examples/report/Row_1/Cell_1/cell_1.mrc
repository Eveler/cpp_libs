<body>
	<parameters>
		<parameter name="$P_3$">
			<parameter_type name="Foreign parameter"/>
			<parameter_data_source value="$P_2$"/>
		</parameter>
	</parameters>
	<keys>
		<key name="$K_6$">
			<key_source_type name="Parameter"/>
			<key_source name="$P_3$"/>
		</key>
		<key name="$K_7$">
			<key_source_type name="SQL"/>
			<key_source name="$S_1$"/>
			<key_data_type name="Text"/>
			<key_data_source value="SELECT $P_3$::text"/>
		</key>
	</keys>
</body>