<report>
	<parameters>
		<parameter name="$P_2$">
			<parameter_type name="Repeater"/>
			<parameter_data_source value="$P_1$"/>
		</parameter>
	</parameters>
	<keys>
		<key name="$K_4$">
			<key_source_type name="SQL"/>
			<key_source name="$S_1$"/>
			<key_data_type name="DateTime"/>
			<key_data_source value="SELECT now()"/>
		</key>
		<key name="$K_5$">
			<key_source_type name="Attachment"/>
			<key_source name="Cell_1"/>
		</key>
	</keys>
</report>