<report>
	<sources>
		<source name="$S_1$">
			<source_type name="SQL"/>
			<source_params driver="QPSQL" host="192.168.91.60" port="5432" database="MFCs"/>
		</source>
	</sources>
	<parameters>
		<parameter name="$P_MAIN_FIRSTDATE$">
			<parameter_type name="InputData"/>
			<parameter_data_type name="Date"/>
			<parameter_label value="С"/>
		</parameter>
		<parameter name="$P_MAIN_LASTDATE$">
			<parameter_type name="InputData"/>
			<parameter_data_type name="Date"/>
			<parameter_label value="По"/>
		</parameter>
		<parameter name="$P_MAIN_VISIBLE_USERNAME_1$">
			<parameter_type name="SQL"/>
			<parameter_source name="$S_1$"/>
			<parameter_data_type name="StringList"/>
			<parameter_data_source><![CDATA[SELECT user_name(u.id)
	FROM users u
	WHERE (u.post=-2066383748 OR u.post=-1869394872) AND u.dismissed=false AND u.isactive=true
		AND (SELECT COALESCE ((SELECT true
			FROM users u1, group_members gm, groups g
			WHERE u1.id=gm.member AND gm.group_id=g.id AND gm.m_type=1 AND g.group_name='специалист ведущий прием' AND u1.id=u.id), false))=true
		AND (SELECT COALESCE ((SELECT true
			FROM users u1, group_members gm, groups g
			WHERE u1.id=gm.member AND gm.group_id=g.id AND gm.m_type=1 AND g.group_name='администратор приёма' AND u1.id=u.id), false))=false
		AND (SELECT COALESCE ((SELECT true
			FROM users u1, group_members gm, groups g
			WHERE u1.id=gm.member AND gm.group_id=g.id AND gm.m_type=1 AND g.group_name='контакт-сектор' AND u1.id=u.id), false))=false
 	ORDER BY user_name(u.id)]]></parameter_data_source>
		</parameter>
		<parameter name="$P_MAIN_VISIBLE_USERNAME_2$">
			<parameter_type name="SQL"/>
			<parameter_source name="$S_1$"/>
			<parameter_data_type name="StringList"/>
			<parameter_data_source><![CDATA[SELECT user_name(u.id)
	FROM users u
	WHERE (u.post=-2066383748 OR u.post=-1869394872) AND u.dismissed=false
		AND (SELECT COALESCE ((SELECT true
			FROM users u1, group_members gm, groups g
			WHERE u1.id=gm.member AND gm.group_id=g.id AND gm.m_type=1 AND g.group_name='контакт-сектор' AND u1.id=u.id), false))=true
 	ORDER BY user_name(u.id)]]></parameter_data_source>
		</parameter>
	</parameters>
	<keys>
		<key name="$FIRST_DATE$">
			<key_source_type name="Parameter"/>
			<key_source name="$P_MAIN_FIRSTDATE$"/>
		</key>
		<key name="$LAST_DATE$">
			<key_source_type name="Parameter"/>
			<key_source name="$P_MAIN_LASTDATE$"/>
		</key>
		<key name="$ROW_1$">
			<key_source_type name="Attachment"/>
			<key_source name="ROW_1"/>
		</key>
		<key name="$ROW_2$">
			<key_source_type name="Attachment"/>
			<key_source name="ROW_2"/>
		</key>
		<key name="$TOTAL_1$">
			<key_source_type name="Attachment"/>
			<key_source name="TOTAL_1"/>
		</key>
		<key name="$DATE$">
			<key_source_type name="SQL"/>
			<key_source name="$S_1$"/>
			<key_data_type name="Date"/>
			<key_data_source><![CDATA[SELECT now()::date]]></key_data_source>
		</key>
	</keys>
</report>