// danwan.c
// update by lsxk@hsbbs ��������

#include <ansi.h>

inherit ITEM;

string long();

void create()
{
	int i, size;
	string name, id, id1;

	string *first_name=({HIR+"��",YEL+"��",HIY+"��",HIG+"��",HIC+"��",HIB+"��",MAG+"��",HIY+"��",HIW+"��",WHT+"��",HIM+"��",CYN+"��"});
	string *first_id=({"chi","cheng","huang","lv","qing","lan","zi","jin","yin","yu","xian","fei"});
	string *second_name=({"ˮ","��","ʯ","��","ɰ","��","��","��","��","��"});
	string *second_id=({"shui","zhu","shi","ji","sha","lin","long","hu","bao","feng"});
	string *third_name=({"��"+NOR,"��"+NOR});
	string *third_id=({"wan", "dan"});

	size = sizeof(first_name);
	i = random(size);
	name = first_name[i];
	id = first_id[i];

	size = sizeof(second_name);
	i = random(size);
	name += second_name[i];
	id += second_id[i];

	size = sizeof(third_name);
	i = random(size);
	name += third_name[i];
	id1 = third_id[i];

	set_name(name, ({id+" "+id1,id,id1}));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", (: long :));
		set("unit", "��");
                set("no_drop", 1);
                set("no_give", 1);
		set("sjsz_item", 1);
		set("value", 2000);
	}
	setup();
}

void init()
{
	object me = this_player(), ob;

	if ( environment() == me ) {
		add_action("do_eat", "fu");
		add_action("do_eat", "eat");
	}

	if ( ! query("secret_obj")) return;

	if ( query("owner") == getuid(me) )
		return;

	ob = find_player(query("owner"));

	if ( ! ob) return;

	if ( ob->query_temp("die_by_from") == me){
		ob->delete_temp("die_by_from");
		CHANNEL_D->do_channel( this_object(), "rumor",sprintf("%sŪ����һ��%s��", me->name(1), query("name")));
		set("owner", getuid(me));
		set("eat_time", uptime());
	}
	return;

}

string long()
{
	string str;

	str = query("name")+"("+capitalize(query("id"))+")\n";
	str += "һ��"+query("name")+"������(fu)�Ժ���";
	switch(query("bonus")) {
		case "combat_exp":	str +="����ʵս����";	break;
		case "max_jingli":	str +="��߾���";	break;
		case "max_neili":	str +="�Ӵ�����";	break;
		case "potential":	str +="����Ǳ��";	break;
		default:		str +="һ��";		break;
	}
	str += "�Ĺ�Ч��\n";
	return str;
}

int do_eat(string arg)
{
	object me = this_player();
        object obj;
        int i, max, lvl;
	string str;

	if (!id(arg)) return 0;

	if ( me->is_busy() || me->is_fighting()) 
		return notify_fail("����æ���ء�\n");

	if ( query("owner") != getuid(me))
		return notify_fail("���ʲô�ط��õ��ģ�\n");

	str = HIW"$N����һ��"+query("name")+HIW"����ʱ���û���Ϊ֮һ��������";
	switch(query("bonus")) {
		case "combat_exp":
			if ( !random(100) )
				i = 4000 + random(2000);
			else
				i = 110 + random(80);

                   if(!query("secret_obj") && query("sjsz_item"))
                       i = i * 5 / 2;
			me->add("combat_exp", i);
			log_file("job/shijian", 
				sprintf("%8s%-10sʳ��%6s���õ�%4d�㾭�顣",
					me->name(1),
					"("+getuid(me)+")",
					query("name"),
					i
				), me
			);
			str += chinese_number(i)+"��ʵս���顣\n"NOR;
			break;
		case "max_jingli":
			i = random(2) + 1;
			me->add("max_jingli", i);
			me->add("eff_jingli", i);
			str += chinese_number(i)+"���������\n"NOR;
			break;
		case "max_neili":
			i = random(2) + 1;
			max = (me->query_skill("force")-me->query_temp("apply/force")) * 8 + me->query("combat_exp") / 1000;
			if ( (me->query("max_neili") - 100 ) < max )
				me->add("max_neili", i);
			str += chinese_number(i)+"�����������\n"NOR;
			break;
		case "potential":
			i = random(50) + 35;
			me->add("potential", i);
			str += chinese_number(i)+"��Ǳ�ܡ�\n"NOR;
			break;
		default :
			return notify_fail("�����⣬�������Ա�㱨��\n");
	}
	message_vision(str, me);
	"/adm/daemons/emoted"->do_emote(me,"taste");
	if ( query("secret_obj"))
		CHANNEL_D->do_channel( this_object(), "rumor",sprintf("���˿���%s������һ��%s��", me->name(1), query("name")));
	destruct(this_object());
	return 1;
}
