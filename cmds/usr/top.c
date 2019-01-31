// top.c yuj@sj 2000-1-16

#define total 100

#include <ansi.h>

inherit F_CLEAN_UP;
inherit F_SAVE;

mapping *ranks;

void create()
{
	seteuid(getuid());
	restore();
}

int remove()
{
	save();
	return 1;
}

string query_save_file()
{
	return "/log/rank";
}

int sort_rank(mapping rank1, mapping rank2)
{
	reset_eval_cost(); // added by snowman@SJ
	return rank2["score"]-rank1["score"];
}

int clean_all()
{
	ranks = ({ });
	return remove();
}

void add_rank(object ob)
{
	int i, score, t = time();
	int exp = ob->query("combat_exp");
	int age = ob->query("mud_age") / 3600;
	mapping rank;
	string party = ob->query("family/family_name");

	// ��ɾ��ԭ�ȼ�¼
	for (i = 0; i < sizeof(ranks); i++)
		if (wiz_level(ranks[i]["id"]) || ranks[i]["id"] == ob->query("id") || ranks[i]["score"] < 1) {
			ranks = ranks[0..i-1] + ranks[i+1..total];
			i--;
		}

	if (wiz_level(ob)) return;
	if (age < 10 || exp < 1) return;
	score = exp / 200 * (ob->query_int()-ob->query_temp("apply/intelligence")
		+ob->query_str()-ob->query_temp("apply/strength")
		+ob->query_dex()-ob->query_temp("apply/dexerity")) / 1000
//		+ exp / age
		+ to_int((ob->query_con()-ob->query_temp("apply/constitution"))
			* ob->query("max_neili") / 40.0 * ob->query("max_neili") / 10000)
		+ to_int((ob->query_con()-ob->query_temp("apply/constitution"))
			* ob->query("max_jingli") / 20.0 * ob->query("max_jingli") / 10000);
	ob->set("score", score);
	if( score < 1 ) return;

	for (i = 0; i < sizeof(ranks); i++)
		if (!LOGIN_D->find_body(ranks[i]["id"]))
			while (ranks[i]["time"]+3600 < t) {
				ranks[i]["time"] += 3600;
				ranks[i]["score"] *= 97;
				ranks[i]["score"] /= 100;
			}
		else ranks[i]["time"] = t;

	if (!sizeof(ranks)) ranks = ({ });
	ranks = sort_array(ranks, (: sort_rank :));

	for (i = 0; i < sizeof(ranks); i++)
		if (score > ranks[i]["score"]) break;
	if (i > total) return;

	if (!stringp(party)) party = "��ͨ����";
	rank =  ([      "id":           ob->query("id"),
			"name":         ob->query("name"),
			"family":       party,
			"exp":          exp,
			"eoh":          exp / age,
			"time":         t,
			"score":        score ]);
	if (!sizeof(ranks))
		ranks = ({ rank });
	else
		ranks = ranks[0..i-1] + ({ rank }) + ranks[i..total];
	save();
}

int main(object me, string arg)
{
	int i, j;
	string str = "\n";
	int flag = wizardp(me), t = time()-3600-119;

	if (me->is_busy())
		return notify_fail("����æ���ء�\n");
	me->start_busy(1);
	if (me->query("combat_exp") > 1000000 && !wiz_level(me))
		add_rank(me);
	str += "              �� �齣�������а� ��\n";
	str += "�������ө������ߩ����������ө����ߩ��ө���������\n";
	str += "�����Ω�     ��     ��    �� ��  �� ���ۺ����۩�\n";
	str += "�ĩ����ة������������������ة��������ة���������\n";
	if (stringp(arg))
		sscanf(arg, "%d", j);
	if (j < 1)
		j = 10;
	if (j > total)
		j = total;
	if (j > sizeof(ranks))
		j = sizeof(ranks);
	for (i = 0; i < j; i++)
		str += sprintf("��%s%|4d  %8s%-10s  %|8s  %|8d" NOR "��%s\n",
			(ranks[i]["id"] == me->query("id"))?HIY BRED:"",
			i+1,
			ranks[i]["name"],
			"("+capitalize(ranks[i]["id"])+")",
			ranks[i]["family"],
			ranks[i]["score"],
			flag?sprintf("%'.'-30s", repeat_string("o", (ranks[i]["time"]-t)/120)):"");
	str += "������������������������������������������������\n";
if (str)
	me->start_more(str);
	return 1;
}

int help(object me)
{
	write("top [1-"+total+"] ��ʾ�齣�������а�� 1 �� "+total+" ����\n");
	return 1;
}
