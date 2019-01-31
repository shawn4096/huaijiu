#include <ansi.h>
#include <combat.h>

inherit F_CLEAN_UP;

string display_attr(int gift, int value);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object ob;
	mapping my;
	string line ,temp ,skill_type;
	object weapon;
	int attack_points, dodge_points, parry_points;

	if (!arg)
		ob = me;
	else if (wizardp(me)) {
		ob = present(arg, environment(me));
		if (!ob) ob = LOGIN_D->find_body(arg);
		if (!ob) ob = find_living(arg);
		if (!ob || !me->visible(ob)) return notify_fail("��Ҫ�쿴˭��״̬��\n");
	} else
		return notify_fail("ֻ����ʦ�ܲ쿴���˵�״̬��\n");

	my = ob->query_entire_dbase();
	line = "\n������"HIW"���齣�������Ͽ���"NOR
		+(ob->query_temp("big5")?"��":"��")+"�����ĩ����ש���������������������������������������\n";
	line += sprintf("��ͷ    �Σ�%-24s����  �أ���%-28s��\n",
		RANK_D->query_rank(ob),
		chinese_number(ob->query_weight()/500)+"�"
	);
	line += sprintf("����    ν��%-24s��%-19s%-19s��\n",
		my["title"]?my["title"]:"��",
		"��  ������"+display_attr(my["str"], ob->query_str())+"��",
		"��  �ǣ���"+display_attr(my["con"], ob->query_con())+"��"
	);
	line += sprintf("����    ����%-24s��%-19s%-19s��\n",
		(my["color"]?my["color"]:"")+my["name"]+NOR"("+capitalize(my["id"])+")",
		"��  ������"+display_attr(my["dex"], ob->query_dex())+"��",
		"��  �ԣ���"+display_attr(my["int"], ob->query_int())+"��"
	);
	line += sprintf("����    �ţ�%-24s������������������������������������������\n",
		my["nickname"]?my["nickname"]+NOR:"��"
	);
	line += sprintf("����    �䣺%-26s��  ����%-30s��\n",
		chinese_number(my["age"])+"��"+(my["month"]?"��"+chinese_number(my["month"])+"����":""),
		CHINESE_D->chinese_date((my["birthday"] - 14*365*24*60) * 60)
	);
	if(objectp(weapon = ob->query_temp("weapon")) ) skill_type = weapon->query("skill_type");
	else {
		mapping prepare = ob->query_skill_prepare();

		if (!sizeof(prepare)) skill_type = "unarmed";
		else skill_type = keys(prepare)[0];
	}
	attack_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_ATTACK);
	parry_points = COMBAT_D->skill_power(ob, "parry", SKILL_USAGE_DEFENSE);
	dodge_points = COMBAT_D->skill_power(ob, "dodge", SKILL_USAGE_DEFENSE);
	line += sprintf("����    ��%-26s����%-9s�㣺%-9s�ܣ�%-2s��\n",
		my["gender"],
		"/cmds/std/look"->tough_level(attack_points, 0, 1),
		"/cmds/std/look"->tough_level(dodge_points, 0, 1),
		"/cmds/std/look"->tough_level(parry_points, 0, 1)
	);
	if (my["divorce"]) temp = "����״��������"+chinese_number(my["divorce"])+"��";
	else temp = "����״����δ��";
	if (mapp(my["marry"]))
	{
		if (ob->query("marry/name"))
			temp = (my["gender"]=="Ů��"?"��    ����"HIR:"��    �ޣ�"HIG)
				+my["marry"]["name"]+"("+capitalize(my["marry"]["id"])+")" NOR;
	};
	line += sprintf("��%-36s%-8s%-14d"NOR"���棺%-10s��\n",
		temp,
		my["shen"] < 0?"��  ����"HIR:"��  ����"HIC,
		(my["shen"] < 0?-1:1)*my["shen"],
		my["rules"]?HIR+chinese_number(my["rules"])+"��"NOR:"��"
	);
	if( base_name(ob) == "/clone/user/user" ){
		line += sprintf("��ɱ    �ˣ�%-26s��  �ң�%-30s��\n",
			my["MKS"]+my["PKS"]?HIY BBLU+chinese_number(my["MKS"] + my["PKS"])+"λ"NOR:"��",
			my["PKS"]?HIY BBLU+chinese_number(my["PKS"])+"λ"NOR:"��"
		);
		line += sprintf("���������׵�����%-60s��\n",
			my["sj_credit"]?HIY BBLU+chinese_number(my["sj_credit"])+"��"NOR:"��"
		);
		line += sprintf("������������%-26s��  Ч��%-14s�ۺ����ۣ�%-6d��\n",
			my["death_count"]?HIM+chinese_number(my["death_count"])+"��"NOR:"��",
			my["death_times"]?HIM+chinese_number(my["death_times"])+"��"NOR:"��",
			my["score"]
		);
	}
	temp = ob->query("family/family_name")?"��"+my["family"]["family_name"]+"��":"����ͨ���ա�";
	temp += ob->query("family/master_name")?"��"+my["family"]["master_name"]+"��":"";
	line += sprintf("��Ǯׯ��%-26sʦ  �У�%-30s��\n",
		my["balance"]/10000?HIY BRED+chinese_number(my["balance"]/10000)+"���ƽ�"NOR:"����",
		HIW+temp+NOR
	);
	if( base_name(ob) == "/clone/user/user" )
		line += sprintf("���ϴ�������%-64s��\n",
			(ob->query("last_death")?ob->query("last_death"):"��δ����")
			+(ob->query("last_killer")?"��"+ob->query("last_killer")+"��":"")
		);
	line += "������������������������������������������������������������������������������\n";

	if (wizardp(me)) {
		line += sprintf(" ��ò[%s] ��Ե[%s] ����[%s]",
			display_attr(my["per"], ob->query_per()),
			display_attr(my["kar"], ob->query_kar()),
			display_attr(my["pur"], my["pur"]));
		line += sprintf(" ����%d(+%d) ����%d ����%d(+%d)\n",
			attack_points/100, ob->query_temp("apply/damage"),
			dodge_points/100,
			parry_points/100, ob->query_temp("apply/armor"));
		if( base_name(ob) == "/clone/user/user" ){
			temp  = "gf("+(my["gf_job"]?my["gf_job"]:"��")+")";
			temp += " dl("+(my["dali_job"]?my["dali_job"]:"��")+")";
			temp += " gb("+(my["gb_job"]?my["gb_job"]:"��")+")";
			temp += " hs("+(my["hs_job"]?my["hs_job"]:"��")+")";
			temp += " wd("+(my["wd_job"]?my["wd_job"]:"��")+")";
			temp += " mj("+(my["mingjiao_job"]?my["mingjiao_job"]:"��")+")";
			temp += " sl("+(my["sl_job"]?my["sl_job"]:"��")+")";
			temp += " ��ʦ("+(my["betrayer"]?my["betrayer"]:"��")+")";
			line += sprintf(" ����(����)��"+temp+"\n");
			if (my["mud_age"] >= 600) {
				line += sprintf(" ���飺%d ÿʮ���ӣ�%.1f ��Ϸʱ�䣺%s\n",
					my["combat_exp"], my["combat_exp"]/(my["mud_age"]/600.0),
					CHINESE_D->chinese_time(my["mud_age"]/600*600)
				);
			}
		}
	}
	if (my["mud_age"] >= 86400)
		line += sprintf(" ƽ��ÿ������ʱ�䣺%s\n",
			CHINESE_D->chinese_time(to_int(my["mud_age"]*400.0/(time()-my["birthday"])*216))
	);
	write(line);
	return 1;
}

string display_attr(int gift, int value)
{
	string str;
	if (value > gift) str = HIY;
	else if (value < gift) str = CYN;
	return str + value + NOR + "/" + gift;
}

int help(object me)
{
write(@HELP
ָ���ʽ : score
	   score <��������>            (��ʦר��)

���ָ�������ʾ���ָ������(��NPC)�Ļ������ϡ�

see also : hp
HELP
);
	return 1;
}
