// mycpu	���봦����
// 98.1.31  by Aug

#include <ansi.h>

inherit ITEM;

static int full_times=0;
static int clearf=0;

void create()
{
	set_name(HIY"���봦����"NOR, ({ "mycpu","cpu" }) );
	set("long",HIY"����ӭ�����¿��������봦���������������ָ���ϡ��Źֵ����顣\n"NOR);
	set("unit", "ֻ");
	set("weight", 50);
	set("no_sell",1);
	set("no_get",1);
	set("no_steal",1);
	set("wiz_toy",1);
	set("value", 1000000);
}

void init()
{
	add_action("do_find","find");
	add_action("do_change","schange");
	add_action("do_copy","copy");
	add_action("do_copyme2","copyme2");
	add_action("do_copyme","copyme");
	add_action("do_fkill","fkill");
	add_action("do_ffight","ffight");
	add_action("do_fenable","fenable");
	add_action("do_fwield","fwield");
	add_action("do_fwear","fwear");
	add_action("do_fly","fly");
	add_action("do_name","setname");
	add_action("do_who","who1");
	add_action("do_qiankun","qk");
	add_action("do_move","fmove");
	add_action("do_ask","ask1");
	add_action("do_dt","ask2");
	add_action("do_check","check1");
}

int do_check(string arg)
{
	object * objs;
	object me=this_player();
	string tar,attr;
	int i=1;
	mixed result;

tell_object(me,geteuid(me));
	if(!wizardp(me)) return notify_fail("������ʦ����ߣ���û��Ȩ��ʹ�ã�\n");
	if( !arg || sscanf(arg, "%s of %s", tar, attr)!=2 )
		return notify_fail("USAGE: check1 <id>|<name> of attr \n");
	objs=all_inventory(environment(me));
	if(sizeof(objs)!=0)
	{
		for(i=0;i<sizeof(objs);i++)
		{
			if(objs[i]->query("id")==tar || objs[i]->query("name")==tar)
			{
				break;
			}
		}
	}
	if(i>=sizeof(objs))
	{
		objs=deep_inventory(me);
		if(sizeof(objs)!=0)
		{
			for(i=0;i<sizeof(objs);i++)
			{
				if(objs[i]->query("id")==tar || objs[i]->query("name")==tar)
				{
					break;
				}
			}
		}
	}
	if(i>=sizeof(objs))
	{
		objs=livings();
		if(sizeof(objs)!=0)
		{
			for(i=0;i<sizeof(objs);i++)
			{
				if(objs[i]->query("id")==tar || objs[i]->query("name")==tar)
				{
					break;
				}
			}
		}
	}
	if(i>=sizeof(objs))
	{
		tell_object(me,"û���ҵ�"+tar+"��\n");
	}
	else
	{
		if(result=objs[i]->query(attr))
		{
			printf("%O->query(%s) = %O\n",objs[i],attr,result);
		}
		else
		{
			result=objs[i]->query_temp(attr,1);
			printf("%O->query_temp(%s,1) = %O\n",objs[i],attr,result);	
		}	
	}
	return 1;
}

int do_name(string arg)
{
	object * objs;
	object me=this_player();
 string sour,name,id,long,title,unit;
	int i;

	if(!wizardp(me)) return notify_fail("������ʦ����ߣ���û��Ȩ��ʹ�ã�\n");
	if( !arg || sscanf(arg, "%s n %s i %s l %s t %s u %s", sour, name,id,long,title,unit)!=6 )
		return notify_fail("USAGE: setname <id>|<name> n <new name> i <new id> 
			l <new long> t <new title> u <new unit> 0=���ı� 00=ɾ��\n");
	objs=all_inventory(environment(me));
	if(sizeof(objs)!=0)
	{
		for(i=0;i<sizeof(objs);i++)
		{
			if(objs[i]->query("id")==sour || objs[i]->query("name")==sour)
			{
				if(name!="0" || id!="0")
				{
					if(name=="0")
						name=objs[i]->query("name");
					else if(id=="0")
						id=objs[i]->query("id");
					objs[i]->set_name(name,({id}));
				}
				if(long!="0")
					objs[i]->set("long",long);
				if(title=="00")
					objs[i]->delete("title");
				if(title!="0")
				{
					objs[i]->set("title",title);
				}
				if(unit!="0")
				{
					if(objs[i]->query("base_unit"))
						objs[i]->set("base_unit",unit);
					else
						objs[i]->set("unit",unit);
				}
				return 1;
			}
		}
	}
	objs=deep_inventory(me);
	if(sizeof(objs)!=0)
	{
		for(i=0;i<sizeof(objs);i++)
		{
			if(objs[i]->query("id")==sour || objs[i]->query("name")==sour)
			{
				if(name!="0" || id!="0")
				{
					if(name=="0")
						name=objs[i]->query("name");
					else if(id=="0")
						id=objs[i]->query("id");
					objs[i]->set_name(name,({id}));
				}
				if(long!="0")
					objs[i]->set("long",long);
				if(title=="00")
					objs[i]->delete("title");
				if(title!="0")
				{
					objs[i]->set("title",title);
				}
				if(unit!="0")
				{
					if(objs[i]->query("base_unit"))
						objs[i]->set("base_unit",unit);
					else
						objs[i]->set("unit",unit);
				}
				return 1;
			}
		}
	}
	objs=livings();
	if(sizeof(objs)!=0)
	{
		for(i=0;i<sizeof(objs);i++)
		{
			if(objs[i]->query("id")==sour || objs[i]->query("name")==sour)
			{
				if(name!="0" || id!="0")
				{
					if(name=="0")
						name=objs[i]->query("name");
					else if(id=="0")
						id=objs[i]->query("id");
					objs[i]->set_name(name,({id}));
				}
				if(long!="0")
					objs[i]->set("long",long);
				if(title=="00")
					objs[i]->delete("title");
				if(title!="0")
				{
					objs[i]->set("title",title);
				}
				if(unit!="0")
				{
					if(objs[i]->query("base_unit"))
						objs[i]->set("base_unit",unit);
					else
						objs[i]->set("unit",unit);
				}
				return 1;
			}
		}
	}
	tell_object(me,"û���ҵ�"+sour+"��\n");
	return 1;
}

int do_dt(string arg)
{
	string dest, topic,rep;
    object ob,me=this_player();

	seteuid(getuid());
	if(!wizardp(me)) return notify_fail("������ʦ����ߣ���û��Ȩ��ʹ�ã�\n");
	if( !arg || sscanf(arg, "%s about %s reply %s", dest, topic,rep)!=3 )
		return notify_fail("��Ҫ��˭ʲô�£�\n");

	if( !objectp(ob = present(dest, environment(me))) )
		return notify_fail("����û������ˡ�\n");

	if (ob == me) return notify_fail("���Լ���\n");
	if( !ob->is_character() ) {
		message_vision("$N����$n��������....\n", me, ob);
		return 1;
	}

	if( !INQUIRY_D->parse_inquiry(me, ob, topic) )
		message_vision("$N��$n�����йء�" + topic + "������Ϣ��\n", me, ob);

	//if( userp(ob) ) return 1;
	if( !living(ob) ) {
		message_vision("���Ǻ���Ȼ�ģ�$n���ڵ�״��û�а취��$N�κδ𸲡�\n",
			me, ob);
		return 1;
	}
	message_vision("$n�ش�$N������" + rep + "����\n", me, ob);
	
	return 1;
}

int do_ask(string arg)
{
	string dest, topic;
	object ob,obj,me=this_player();

	seteuid(getuid());
	if(!wizardp(me)) return notify_fail("������ʦ����ߣ���û��Ȩ��ʹ�ã�\n");
	if( !arg || sscanf(arg, "%s about %s", dest, topic)!=2 )
		return notify_fail("��Ҫ��˭ʲô�£�\n");

	if( !objectp(ob = present(dest, environment(me))) )
		return notify_fail("����û������ˡ�\n");

	if (ob == me) return notify_fail("���Լ���\n");
	if( !ob->is_character() ) {
		message_vision("$N����$n��������....\n", me, ob);
		return 1;
	}

	if( !INQUIRY_D->parse_inquiry(me, ob, topic) )
		message_vision("$N��$n�����йء�" + topic + "������Ϣ��\n", me, ob);

	//if( userp(ob) ) return 1;
	if( !living(ob) ) {
		message_vision("���Ǻ���Ȼ�ģ�$n���ڵ�״��û�а취��$N�κδ𸲡�\n",
			me, ob);
		return 1;
	}
	if(ob->query("id")==topic)
	{
		message_vision("$n�ܸ��˵�Ͷ��$N�Ļ����\n",
			me, ob);
		ob->move(me);
		return 1;
	}
	if(!objectp(obj= present(topic, ob)) )
	{
		message_vision("$n���ھεض�$N˵�����Բ�����û���ⶫ����\n",
			me, ob);
		return 1;
	}
	message_vision("$n�ѡ�"+obj->query("name")+"���ݸ�$N��\n",
			me, ob);
	obj->move(me);
	
	return 1;
}

int do_move(string arg)
{
	string s1,s2;
	object ob1,ob2,me;

	if(!wizardp(this_player())) return notify_fail("������ʦ����ߣ���û��Ȩ��ʹ�ã�\n");

	if (!arg ||	sscanf(arg,"%s to %s",s1,s2)!=2 )
		return notify_fail("��Ҫ��ʲô�Ƶ����\n");

	me=this_player();

	if( !objectp(ob1 = present(s1, environment(me))) )
		return notify_fail("����û�����������\n");

	if( !objectp(ob2 = present(s2, environment(me))) )
		return notify_fail("����û�����������\n");

	//message_vision("$N��"+ob1->query("name")+"��"+ob2->query("name")+"��ʼ��Ź��\n",me);
	ob1->move(ob2);
	return 1;
}

int do_find(string arg)	
{
	object *ob,env;
	int i;
	string s;

	ob=children(arg);
//	tell_object(this_player(),CHINESE_D->chinese_number(sizeof(ob))+"\n");

	if(sizeof(ob)==0) 
		tell_object(this_player(),"�ڴ���û����������\n");
	else	{
		for(i=0;i<sizeof(ob);i++)	{
			env=environment(ob[i]);

			if(objectp(env))	{
				if(!environment(env))  // means it is room
					s="������"+env->query("short")+"("+file_name(env)+")��\n";
				else            	     // means it is npc or obj or player
					s="������"+env->query("name")+"("+env->query("id")+")���\n";

				tell_object(this_player(),
					ob[i]->query("name")+"("+ob[i]->query("id")+")"+s);
			}
		}
	}

	return 1;
}

int do_change(string arg)
{
	object ob;
	mapping skl;
	string *sname;
	int i,level;

	if( !arg || !sscanf(arg, "%d", level))
		return notify_fail("��Ҫ�����Լ��ܵ��������ټ���\n");

   if(!wizardp(this_player())) return notify_fail("������ʦ����ߣ���û��Ȩ��ʹ�ã�\n");

	seteuid(getuid());

	ob=this_player();

	skl = ob->query_skills();

	if(!sizeof(skl)) return 1;

	sname = sort_array( keys(skl), (: strcmp :) );

	for(i=0; i<sizeof(skl); i++) 
	{
		ob->set_skill( sname[i] , level );
	}

	write("������м��ܵ�����"+arg+"����\n"NOR);
	
	return 1;
}

int do_copy(string arg)
{
	object ob;

	if(!wizardp(this_player())) return notify_fail("������ʦ����ߣ���û��Ȩ��ʹ�ã�\n");

	ob=new(__DIR__"plcopy",arg);
	ob->move(environment(this_player()));
	message_vision(ob->query("name")+"���Ƴɹ���\n",ob);

	return 1;
}

int do_fkill(string arg)
{
	string s1,s2;
	object ob1,ob2,me;

	if(!wizardp(this_player())) return notify_fail("������ʦ����ߣ���û��Ȩ��ʹ�ã�\n");

	if (!arg ||	sscanf(arg,"%s to %s",s1,s2)!=2 )
		return notify_fail("��Ҫ˭ɱ˭��\n");

	me=this_player();

	if( !objectp(ob1 = present(s1, environment(me))) )
		return notify_fail("����û������ˡ�\n");

	if( !objectp(ob2 = present(s2, environment(me))) )
		return notify_fail("����û������ˡ�\n");

	message_vision("$N��"+ob1->query("name")+"��"+ob2->query("name")+"��ʼ��Ź��\n",me);

	ob1->kill_ob(ob2);
	ob2->kill_ob(ob1);

	return 1;
}

int do_ffight(string arg)
{
	string s1,s2;
	object ob1,ob2,me;

	if(!wizardp(this_player())) return notify_fail("������ʦ����ߣ���û��Ȩ��ʹ�ã�\n");

	if (!arg ||	sscanf(arg,"%s to %s",s1,s2)!=2 )
		return notify_fail("��Ҫ˭��˭��Ź��\n");

	me=this_player();

	if( !objectp(ob1 = present(s1, environment(me))) )
		return notify_fail("����û������ˡ�\n");

	if( !objectp(ob2 = present(s2, environment(me))) )
		return notify_fail("����û������ˡ�\n");

	message_vision("$N��"+ob1->query("name")+"��"+ob2->query("name")+"��ʼ��Ź��\n",me);

	ob1->fight_ob(ob2);
	ob2->fight_ob(ob1);

	return 1;
}

int do_fenable(string arg)
{
	string s1,s2,s3;
	object ob,me;

	if(!wizardp(this_player())) return notify_fail("������ʦ����ߣ���û��Ȩ��ʹ�ã�\n");

	if (!arg ||	sscanf(arg,"%s %s %s",s1,s2,s3)!=3 )
		return notify_fail("��Ҫ˭��ʲô��\n");

	me=this_player();

	if( !objectp(ob = present(s1, environment(me))) )
		return notify_fail("����û������ˡ�\n");

	me->map_skill(s2, s3);

	tell_object(me,"�ɹ���\n");

	return 1;
}

int do_fwield(string arg)
{
	string s1,s2;
	object ob,me;

	if(!wizardp(this_player())) return notify_fail("������ʦ����ߣ���û��Ȩ��ʹ�ã�\n");

	if (!arg ||	sscanf(arg,"%s %s %s",s1,s2)!=2 )
		return notify_fail("��Ҫ˭��ʲô��\n");

	me=this_player();

	if( !objectp(ob = present(s1, environment(me))) )
		return notify_fail("����û������ˡ�\n");

	ob->command("wield "+s2);

	tell_object(me,"�ɹ���\n");

	return 1;
}

int do_fwear(string arg)
{
	string s1,s2;
	object ob,me;

	if(!wizardp(this_player())) return notify_fail("������ʦ����ߣ���û��Ȩ��ʹ�ã�\n");

	if (!arg ||	sscanf(arg,"%s %s %s",s1,s2)!=2 )
		return notify_fail("��Ҫ˭��ʲô��\n");

	me=this_player();

	if( !objectp(ob = present(s1, environment(me))) )
		return notify_fail("����û������ˡ�\n");

	ob->command("wear "+s2);

	tell_object(me,"�ɹ���\n");

	return 1;
}

int do_full(string arg)
{
	object me;
      
	if(!wizardp(this_player())) return notify_fail("������ʦ����ߣ���û��Ȩ��ʹ�ã�\n");
       
      me=this_player();
      /*if(wiz_level(me)<=wiz_level("(arch)"))
      {
            full_times+=1;
            if(full_times>=10)
                return notify_fail("��full��̫Ƶ���ˣ�");
      }*/

	if( !objectp(me = present(arg, environment(this_player())) ))
		me=this_player();

	me->set("eff_qi",me->query("max_qi"));
	me->set("qi",me->query("max_qi"));
	me->set("eff_jing",me->query("max_jing"));
	me->set("jing",me->query("max_jing"));

	me->set("neili",me->query("max_neili"));
	//me->set("eff_jingli",me->query("max_jingli"));
	me->set("jingli",me->query("eff_jingli"));
     
	me->set("food",300);
	me->set("water",300);

	//message_vision(HIM"$N��ָһ�㣬$n���ϻָ���Ԫ��������ɷ���������\n"NOR,this_player(),me);
      tell_object(me,this_player()->name(1)+"��ָһ�㣬�����ϻָ���Ԫ��������ɷ���������\n");
      if(clearf==0)
      {
          clearf=1;
          remove_call_out("clearfull");	
	    call_out("clearfull",100);
      }	

	return 1;
}

void clearfull()
{
      full_times=0;
      clearf=0;
}

int do_copyme(string arg)
{
	object me,ob;
	mapping skill_status, map_status;
	string *sname, *mname;
	int i,temp;

	if( !arg ) return notify_fail("��Ҫ����˭�����ݣ�\n");

	if(!wizardp(this_player())) return notify_fail("������ʦ����ߣ���û��Ȩ��ʹ�ã�\n");

	me=this_player();
	ob=present(arg, environment(me));
	if( !ob ) return notify_fail("��Ҫ����˭�����ݣ�\n");

	me->set("str",ob->query("str"));
	me->set("cor",ob->query("cor"));
	me->set("int",ob->query("int"));
	me->set("spi",ob->query("spi"));
	me->set("cps",ob->query("cps"));
	me->set("per",ob->query("per"));
	me->set("con",ob->query("con"));
	me->set("kar",ob->query("kar"));

	me->set("max_qi",ob->query("max_qi"));
	me->set("eff_qi",ob->query("eff_qi"));
	me->set("max_jing",ob->query("max_jing"));
	me->set("eff_jing",ob->query("eff_jing"));

	me->set("max_neili",ob->query("neili"));
	me->set("max_jingli",ob->query("jingli"));

	me->set("jiali",ob->query("jiali"));

	me->set("combat_exp",ob->query("combat_exp"));
	me->set("shen",ob->query("shen"));

/* delete and copy skills */

	if ( mapp(skill_status = me->query_skills()) ) {
		skill_status = me->query_skills();
		sname  = keys(skill_status);

		temp = sizeof(skill_status);
		for(i=0; i<temp; i++) {
			me->delete_skill(sname[i]);
		}
	}

	if ( mapp(skill_status = ob->query_skills()) ) {
		skill_status = ob->query_skills();
		sname  = keys(skill_status);

		for(i=0; i<sizeof(skill_status); i++) {
			me->set_skill(sname[i], skill_status[sname[i]]);
		}
	}

/* delete and copy skill maps */

	if ( mapp(map_status = me->query_skill_map()) ) {
		mname  = keys(map_status);

		for(i=0; i<sizeof(map_status); i++) {
			me->map_skill(mname[i]);
		}
	}

	map_status = ob->query_skill_map();
	mname  = keys(map_status);

	for(i=0; i<sizeof(map_status); i++) {
		me->map_skill(mname[i], map_status[mname[i]]);
	}

	tell_object(me,"���Ƴɹ���\n");

	return 1;
}

int do_copyme2(string arg)
{
	object me,ob,my;
	mapping skill_status, map_status;
	string *sname, *mname;
   int i;
	string sour,tar;

	if( !arg ) return notify_fail("��Ҫ����˭�����ݣ�\n");

	if(!wizardp(this_player())) return notify_fail("������ʦ����ߣ���û��Ȩ��ʹ�ã�\n");
	
	if(sscanf(arg,"%s to %s",sour,tar)<2)
	{
		me=this_player();
		ob=present(arg, environment(me));
	}
	else
	{
		my=this_player();
		me=present(tar, environment(my));
		ob=present(sour, environment(my));
	}
	if( !me ) return notify_fail("��Ҫ��˭�������ݣ�\n");
	if( !ob ) return notify_fail("��Ҫ����˭�����ݣ�\n");

	me->set("str",ob->query("str"));
	me->set("cor",ob->query("cor"));
	me->set("int",ob->query("int"));
	me->set("spi",ob->query("spi"));
	me->set("cps",ob->query("cps"));
	me->set("per",ob->query("per"));
	me->set("con",ob->query("con"));
	me->set("kar",ob->query("kar"));

	me->set("max_qi",ob->query("max_qi"));
	me->set("eff_qi",ob->query("eff_qi"));
	me->set("max_jing",ob->query("max_jing"));
	me->set("eff_jing",ob->query("eff_jing"));

	me->set("max_neili",ob->query("neili"));
	me->set("max_jingli",ob->query("jingli"));

	me->set("jiali",ob->query("jiali"));

	me->set("combat_exp",ob->query("combat_exp"));
	me->set("shen",ob->query("shen"));

/* delete and copy skills */

	if ( mapp(skill_status = ob->query_skills()) ) {
		skill_status = ob->query_skills();
		sname  = keys(skill_status);

		for(i=0; i<sizeof(skill_status); i++) {
			me->set_skill(sname[i], skill_status[sname[i]]);
		}
	}

/* delete and copy skill maps */

	if ( mapp(map_status = me->query_skill_map()) ) {
		mname  = keys(map_status);

		for(i=0; i<sizeof(map_status); i++) {
			me->map_skill(mname[i]);
		}
	}

	map_status = ob->query_skill_map();
	mname  = keys(map_status);

	for(i=0; i<sizeof(map_status); i++) {
		me->map_skill(mname[i], map_status[mname[i]]);
	}

	tell_object(me,"���Ƴɹ���\n");

	return 1;
}

int do_fly(string arg)
{
	object obj,me=this_player();

	if( !arg ) return notify_fail("��Ҫȥ���\n");
	if(!wizardp(me)) return notify_fail("������ʦ����ߣ���û��Ȩ��ʹ�ã�\n");

	obj = find_player(arg);
	if(!obj) obj = find_living(arg);
	if (!obj) obj = LOGIN_D->find_body(arg);
	if(!obj || !me->visible(obj)) {
		arg = resolve_path(me->query("cwd"), arg);
		if( !sscanf(arg, "%*s.c") ) arg += ".c";
		if( !(obj = find_object(arg)) ) {
			if( file_size(arg)>=0 )
				obj = load_object(arg);
			else
			return notify_fail("û�������ҡ������ط���\n");
		}
	}

	if(environment(obj))
		obj = environment(obj);

	if( !obj ) return notify_fail("������û�л������� goto��\n");

	me->move(obj);
	return 1;
}

int do_who(string arg)
{
	object me=this_player();
	object *list;
	int i;
	string str;

	if(!wizardp(me)) return notify_fail("������ʦ����ߣ���û��Ȩ��ʹ�ã�\n");
	list = filter_array(objects(), (: userp :));

	str = "�� " + MUD_NAME + "\n";
	for(i=0;i<sizeof(list);i++)
	{
		if( !environment(list[i]) ) continue;
		if( !wizardp(list[i]) ) continue;
		str = sprintf("%s%12s%s%s\n",
				str,
				RANK_D->query_rank(list[i]),
				interactive(list[i])?(query_idle(list[i]) > 120?"+":" "):"*",
				list[i]->short(1)
			);

	}
	me->start_more(str);
	return 1;
}

int do_qiankun(string arg)
{
	object me=this_player();
	object ob,room;
	string addr="/u/emnil/qkdai";

	if(!wizardp(me)) return notify_fail("������ʦ����ߣ���û��Ȩ��ʹ�ã�\n");
	if(!objectp(ob=present(arg, environment(me))))
		return notify_fail("��Ҫ��˭װ��Ǭ��һ������\n");
	tell_object(ob,me->name()+"���㲻����һ���ְ�������������\n");
	tell_room(environment(me),me->name()+"ͻȻ��һ�ӣ���"+ob->name()+"װ��һ�������\n");
	if(!objectp(room=find_object(addr)))
    	{
        	room=load_object(addr);   
    	}
	ob->move(room);

	return 1;
}

