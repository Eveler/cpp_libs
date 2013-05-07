<report>
	<parameters>
		<parameter name="$P_ATTACH_FIRSTDATE_3$">
			<parameter_type name="Foreign parameter"/>
			<parameter_source name="$P_MAIN_FIRSTDATE$"/>
		</parameter>
		<parameter name="$P_ATTACH_LASTDATE_3$">
			<parameter_type name="Foreign parameter"/>
			<parameter_source name="$P_MAIN_LASTDATE$"/>
		</parameter>
	</parameters>
	<keys>
		<key name="$COL_2$">
			<key_source_type name="SQL with parameters"/>
			<key_source name="$S_1$"/>
			<key_data_type name="Time"/>
			<key_data_source><![CDATA[SELECT min(q_2."Время обслуживания")::time FROM (SELECT "Время обслуживания", "Специалист принявший обращение", "Дата/время обращения"::date AS "Дата обращения"
	FROM (SELECT ( SELECT (cwt.enddate - cwt.startdate)::time without time zone AS "time"
                   FROM ctrldate_worktime cwt, ctrldate_worktime_declars cwtd, docpaths dp1
                  WHERE dp1.id = dp.id AND cwtd.declars_id = dp1.declarid AND cwtd.ctrldate_worktime_id = cwt.id AND cwt.workstate_id = 3
			AND dp1.procname = pac.proc_tbl_id AND (dp1.startdate::date = cwt.startdate::date AND pac.appeal_types_priority = 1
				OR dp1.enddate::date = cwt.startdate::date AND pac.appeal_types_priority = 2)
			AND NOT (EXISTS ( SELECT cwtc.id FROM ctrldate_worktime_cons cwtc WHERE cwtc.ctrldate_worktime_id = cwt.id))
                  ORDER BY cwt.startdate
                 LIMIT 1) AS "Время обслуживания",
                 COALESCE(( SELECT ( SELECT user_name(u1.id)
                           FROM users u1
                          WHERE u1.id = dp.operator) FROM procs_appeals_conf pac_2
			WHERE pac.id = pac_2.id AND pac_2.appeal_types_priority = 1),
                  ( SELECT ( SELECT user_name(u1.id)
                           FROM users u1
                          WHERE u1.id = dp.operator_2)
                   FROM procs_appeals_conf pac_2
                  WHERE pac.id = pac_2.id AND pac_2.appeal_types_priority = 2)) AS "Специалист принявший обращение",
                 COALESCE(( SELECT dp.startdate
                   FROM procs_appeals_conf pac_2
                  WHERE pac.id = pac_2.id AND pac_2.appeal_types_priority = 1), ( SELECT dp.enddate
                   FROM procs_appeals_conf pac_2
                  WHERE pac.id = pac_2.id AND pac_2.appeal_types_priority = 2)) AS "Дата/время обращения",
                  d.declarnum
	FROM declars d, docpaths dp, procs_appeals_conf pac WHERE d.id=dp.declarid AND dp.procname = pac.proc_tbl_id ) q_1
	WHERE q_1."Время обслуживания" IS NOT NULL AND "Дата/время обращения">='$P_ATTACH_FIRSTDATE_3$' AND "Дата/время обращения"<='$P_ATTACH_LASTDATE_3$'
	ORDER BY "Специалист принявший обращение", "Дата/время обращения"::date, "Время обслуживания") q_2
	WHERE q_2."Специалист принявший обращение" IS NOT NULL]]>
			</key_data_source>
		</key>
		<key name="$COL_3$">
			<key_source_type name="SQL with parameters"/>
			<key_source name="$S_1$"/>
			<key_data_type name="Time"/>
			<key_data_source><![CDATA[SELECT avg(q_2."Время обслуживания")::time FROM (SELECT "Время обслуживания", "Специалист принявший обращение", "Дата/время обращения"::date AS "Дата обращения"
	FROM (SELECT ( SELECT (cwt.enddate - cwt.startdate)::time without time zone AS "time"
                   FROM ctrldate_worktime cwt, ctrldate_worktime_declars cwtd, docpaths dp1
                  WHERE dp1.id = dp.id AND cwtd.declars_id = dp1.declarid AND cwtd.ctrldate_worktime_id = cwt.id AND cwt.workstate_id = 3
			AND dp1.procname = pac.proc_tbl_id AND (dp1.startdate::date = cwt.startdate::date AND pac.appeal_types_priority = 1
				OR dp1.enddate::date = cwt.startdate::date AND pac.appeal_types_priority = 2)
			AND NOT (EXISTS ( SELECT cwtc.id FROM ctrldate_worktime_cons cwtc WHERE cwtc.ctrldate_worktime_id = cwt.id))
                  ORDER BY cwt.startdate
                 LIMIT 1) AS "Время обслуживания",
                 COALESCE(( SELECT ( SELECT user_name(u1.id)
                           FROM users u1
                          WHERE u1.id = dp.operator) FROM procs_appeals_conf pac_2
			WHERE pac.id = pac_2.id AND pac_2.appeal_types_priority = 1),
                  ( SELECT ( SELECT user_name(u1.id)
                           FROM users u1
                          WHERE u1.id = dp.operator_2)
                   FROM procs_appeals_conf pac_2
                  WHERE pac.id = pac_2.id AND pac_2.appeal_types_priority = 2)) AS "Специалист принявший обращение",
                 COALESCE(( SELECT dp.startdate
                   FROM procs_appeals_conf pac_2
                  WHERE pac.id = pac_2.id AND pac_2.appeal_types_priority = 1), ( SELECT dp.enddate
                   FROM procs_appeals_conf pac_2
                  WHERE pac.id = pac_2.id AND pac_2.appeal_types_priority = 2)) AS "Дата/время обращения",
                  d.declarnum
	FROM declars d, docpaths dp, procs_appeals_conf pac WHERE d.id=dp.declarid AND dp.procname = pac.proc_tbl_id ) q_1
	WHERE q_1."Время обслуживания" IS NOT NULL AND "Дата/время обращения">='$P_ATTACH_FIRSTDATE_3$' AND "Дата/время обращения"<='$P_ATTACH_LASTDATE_3$'
	ORDER BY "Специалист принявший обращение", "Дата/время обращения"::date, "Время обслуживания") q_2
	WHERE q_2."Специалист принявший обращение" IS NOT NULL]]>
			</key_data_source>
		</key>
		<key name="$COL_4$">
			<key_source_type name="SQL with parameters"/>
			<key_source name="$S_1$"/>
			<key_data_type name="Time"/>
			<key_data_source><![CDATA[SELECT max(q_2."Время обслуживания")::time FROM (SELECT "Время обслуживания", "Специалист принявший обращение", "Дата/время обращения"::date AS "Дата обращения"
	FROM (SELECT ( SELECT (cwt.enddate - cwt.startdate)::time without time zone AS "time"
                   FROM ctrldate_worktime cwt, ctrldate_worktime_declars cwtd, docpaths dp1
                  WHERE dp1.id = dp.id AND cwtd.declars_id = dp1.declarid AND cwtd.ctrldate_worktime_id = cwt.id AND cwt.workstate_id = 3
			AND dp1.procname = pac.proc_tbl_id AND (dp1.startdate::date = cwt.startdate::date AND pac.appeal_types_priority = 1
				OR dp1.enddate::date = cwt.startdate::date AND pac.appeal_types_priority = 2)
			AND NOT (EXISTS ( SELECT cwtc.id FROM ctrldate_worktime_cons cwtc WHERE cwtc.ctrldate_worktime_id = cwt.id))
                  ORDER BY cwt.startdate
                 LIMIT 1) AS "Время обслуживания",
                 COALESCE(( SELECT ( SELECT user_name(u1.id)
                           FROM users u1
                          WHERE u1.id = dp.operator) FROM procs_appeals_conf pac_2
			WHERE pac.id = pac_2.id AND pac_2.appeal_types_priority = 1),
                  ( SELECT ( SELECT user_name(u1.id)
                           FROM users u1
                          WHERE u1.id = dp.operator_2)
                   FROM procs_appeals_conf pac_2
                  WHERE pac.id = pac_2.id AND pac_2.appeal_types_priority = 2)) AS "Специалист принявший обращение",
                 COALESCE(( SELECT dp.startdate
                   FROM procs_appeals_conf pac_2
                  WHERE pac.id = pac_2.id AND pac_2.appeal_types_priority = 1), ( SELECT dp.enddate
                   FROM procs_appeals_conf pac_2
                  WHERE pac.id = pac_2.id AND pac_2.appeal_types_priority = 2)) AS "Дата/время обращения",
                  d.declarnum
	FROM declars d, docpaths dp, procs_appeals_conf pac WHERE d.id=dp.declarid AND dp.procname = pac.proc_tbl_id ) q_1
	WHERE q_1."Время обслуживания" IS NOT NULL AND "Дата/время обращения">='$P_ATTACH_FIRSTDATE_3$' AND "Дата/время обращения"<='$P_ATTACH_LASTDATE_3$'
	ORDER BY "Специалист принявший обращение", "Дата/время обращения"::date, "Время обслуживания") q_2
	WHERE q_2."Специалист принявший обращение" IS NOT NULL]]>
			</key_data_source>
		</key>
		<key name="$COL_5$">
			<key_source_type name="SQL with parameters"/>
			<key_source name="$S_1$"/>
			<key_data_type name="Integer"/>
			<key_data_source><![CDATA[SELECT COUNT(*) AS dp_cnt FROM docpaths_prelim_view dpw
				WHERE "Дата/время обращения"::date>='$P_ATTACH_FIRSTDATE_3$'::date
					AND "Дата/время обращения"::date<='$P_ATTACH_LASTDATE_3$'::date
					AND appeal_type=1
					AND "Время обслуживания"::time>'00:30:59'::time]]>
			</key_data_source>
		</key>
		<key name="$COL_6$">
			<key_source_type name="SQL with parameters"/>
			<key_source name="$S_1$"/>
			<key_data_type name="Integer"/>
			<key_data_source><![CDATA[SELECT COUNT(*) AS dp_cnt FROM docpaths_prelim_view dpw
				WHERE "Дата/время обращения"::date>='$P_ATTACH_FIRSTDATE_3$'::date
					AND "Дата/время обращения"::date<='$P_ATTACH_LASTDATE_3$'::date
					AND appeal_type=1
					AND "Время обслуживания"::time>'00:15:59'::time]]>
			</key_data_source>
		</key>
		<key name="$COL_7$">
			<key_source_type name="SQL with parameters"/>
			<key_source name="$S_1$"/>
			<key_data_type name="Integer"/>
			<key_data_source><![CDATA[SELECT COUNT(*) AS dp_cnt FROM docpaths_prelim_view dpw
				WHERE "Дата/время обращения"::date>='$P_ATTACH_FIRSTDATE_3$'::date
					AND "Дата/время обращения"::date<='$P_ATTACH_LASTDATE_3$'::date
					AND appeal_type=2
					AND "Время обслуживания"::time>'00:15:59'::time]]>
			</key_data_source>
		</key>
		<key name="$COL_8$">
			<key_source_type name="SQL with parameters"/>
			<key_source name="$S_1$"/>
			<key_data_type name="Integer"/>
			<key_data_source><![CDATA[SELECT count(q_2."Время обслуживания")
	FROM (SELECT "Время обслуживания", "Специалист принявший обращение", "Дата/время обращения"::date AS "Дата обращения"
		FROM (SELECT (cwt.enddate - cwt.startdate)::time without time zone AS "Время обслуживания",
			user_name(u.id) AS "Специалист принявший обращение", cs.cons_date AS "Дата/время обращения"
			FROM consultations cs, users u, ctrldate_worktime cwt, ctrldate_worktime_cons cwtc
			WHERE u.post=-2066383748 AND u.dismissed=FALSE AND u.isactive=TRUE
				AND cs.users_id = u.id AND cwtc.consultations_id = cs.id AND cwt.id = cwtc.ctrldate_worktime_id
				AND cwt.workstate_id = 3 AND NOT cs.cons_num LIKE '%Р000ЛР%' AND NOT cs.cons_num LIKE '%Р000ТР%'
				AND NOT cs.cons_num LIKE '%Р000СР%') AS q_1
		WHERE q_1."Время обслуживания" IS NOT NULL AND "Дата/время обращения">='$P_ATTACH_FIRSTDATE_3$' AND "Дата/время обращения"<='$P_ATTACH_LASTDATE_3$') q_2
	WHERE q_2."Время обслуживания">'00:15:59'::time without time zone AND q_2."Специалист принявший обращение" IS NOT NULL]]>
			</key_data_source>
		</key>
		<key name="$COL_9$">
			<key_source_type name="SQL with parameters"/>
			<key_source name="$S_1$"/>
			<key_data_type name="Integer"/>
			<key_data_source><![CDATA[SELECT (dp_q.dp_cnt+cons_q.cons_cnt) AS cnt
	FROM (SELECT COUNT(*) AS dp_cnt FROM docpaths_prelim_view dpw
		WHERE dpw."Дата/время обращения"::date>='$P_ATTACH_FIRSTDATE_3$'::date
			AND dpw."Дата/время обращения"::date<='$P_ATTACH_LASTDATE_3$'::date) dp_q,
	(SELECT count(*) AS cons_cnt
		FROM (SELECT cs.id, (cwt.enddate - cwt.startdate)::time without time zone AS "Время обслуживания",
			user_name(u.id) AS "Специалист принявший обращение", cs.cons_date AS "Дата/время обращения"
			FROM consultations cs, users u, ctrldate_worktime cwt, ctrldate_worktime_cons cwtc
			WHERE cs.users_id = u.id AND cwtc.consultations_id = cs.id AND cwt.id = cwtc.ctrldate_worktime_id
				AND cwt.workstate_id = 3 AND NOT cs.cons_num LIKE '%Р000ЛР%' AND NOT cs.cons_num LIKE '%Р000ТР%'
				AND NOT cs.cons_num LIKE '%Р000СР%') AS q_1
		WHERE q_1."Время обслуживания" IS NOT NULL AND "Дата/время обращения"::date>='$P_ATTACH_FIRSTDATE_3$'::date
			AND "Дата/время обращения"::date<='$P_ATTACH_LASTDATE_3$'::date) cons_q]]>
			</key_data_source>
		</key>
		<key name="$COL_10$">
			<key_source_type name="SQL with parameters"/>
			<key_source name="$S_1$"/>
			<key_data_type name="Integer"/>
			<key_data_source><![CDATA[SELECT (cnt_15.cnt::real/cnt_all.cnt::real*100.)::integer
	FROM (SELECT (dp_q.dp_cnt+cons_q.cons_cnt) AS cnt
			FROM (SELECT COUNT(*) AS dp_cnt FROM docpaths_prelim_view dpw
				WHERE "Дата/время обращения"::date>='$P_ATTACH_FIRSTDATE_3$'::date
					AND "Дата/время обращения"::date<='$P_ATTACH_LASTDATE_3$'::date) dp_q,
			(SELECT count(*) AS cons_cnt
				FROM (SELECT cs.id, (cwt.enddate - cwt.startdate)::time without time zone AS "Время обслуживания",
					user_name(u.id) AS "Специалист принявший обращение", cs.cons_date AS "Дата/время обращения"
					FROM consultations cs, users u, ctrldate_worktime cwt, ctrldate_worktime_cons cwtc
					WHERE cs.users_id = u.id AND cwtc.consultations_id = cs.id AND cwt.id = cwtc.ctrldate_worktime_id
						AND cwt.workstate_id = 3 AND NOT cs.cons_num LIKE '%Р000ЛР%' AND NOT cs.cons_num LIKE '%Р000ТР%'
						AND NOT cs.cons_num LIKE '%Р000СР%') AS q_1
				WHERE "Время обслуживания" IS NOT NULL AND "Дата/время обращения"::date>='$P_ATTACH_FIRSTDATE_3$'::date
					AND "Дата/время обращения"::date<='$P_ATTACH_LASTDATE_3$'::date) cons_q) cnt_all,
		(SELECT (dp_q.dp_cnt+cons_q.cons_cnt) AS cnt
			FROM (SELECT COUNT(*) AS dp_cnt FROM docpaths_prelim_view dpw
				WHERE "Дата/время обращения"::date>='$P_ATTACH_FIRSTDATE_3$'::date
					AND "Дата/время обращения"::date<='$P_ATTACH_LASTDATE_3$'::date
					AND "Время обслуживания"::time<'00:16:00'::time) dp_q,
			(SELECT count(*) AS cons_cnt
				FROM (SELECT cs.id, (cwt.enddate - cwt.startdate)::time without time zone AS "Время обслуживания",
					user_name(u.id) AS "Специалист принявший обращение", cs.cons_date AS "Дата/время обращения"
					FROM consultations cs, users u, ctrldate_worktime cwt, ctrldate_worktime_cons cwtc
					WHERE cs.users_id = u.id AND cwtc.consultations_id = cs.id AND cwt.id = cwtc.ctrldate_worktime_id
						AND cwt.workstate_id = 3 AND NOT cs.cons_num LIKE '%Р000ЛР%' AND NOT cs.cons_num LIKE '%Р000ТР%'
						AND NOT cs.cons_num LIKE '%Р000СР%') AS q_1
				WHERE "Время обслуживания" IS NOT NULL AND "Дата/время обращения"::date>='$P_ATTACH_FIRSTDATE_3$'::date
					AND "Дата/время обращения"::date<='$P_ATTACH_LASTDATE_3$'::date
					AND "Время обслуживания"::time<'00:16:00'::time) cons_q) cnt_15]]>
			</key_data_source>
		</key>
	</keys>
</report>

