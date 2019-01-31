#include <ansi.h>

inherit ITEM;

object me,jf;
int checkteam();
void destructing(object);

int perform_action(string action)
{
	string martial_skill, act;
	
	if( sscanf(action, "%s.%s", martial_skill, act) != 2 )
		return 0;
	martial_skill = jf->query_skill_mapped(martial_skill);
	if( stringp(martial_skill) )
		return SKILL_D(martial_skill)->perform_action(this_object(), act);	      
}

void create()
{
	set_name(HIR"�ڳ�"NOR, ({ "silver cart", "cart", "biao che" }) );
	set_weight(300000);
	set("no_get", 1);
	set("no_get_from", 1);
	set_max_encumbrance(80000);
	set("unit", "��");
	set("long", "һ����������ڳ���������Ÿ����ھֵ����졣");
	set("closed", 1);
	set("value", 2000);
	set("no_return",1);
	set("location",1);
	set("no_clean_up",1);
}

int is_container() {return 1;}

void init()
{
	add_action("do_open","open");
	add_action("do_close","close");
	if (this_player()->query_temp("protecting")==this_object()) {
		add_action("do_attack","attack");
		add_action("do_driver","driver");
		add_action("do_finish","finish");
	}
}

int do_close(string arg)
{
	object ob=this_object();
	me = this_player();
	if(arg != "cart" && arg != "silver cart")
		return notify_fail("��Ҫ����ʲô��\n");
	message_vision("$N��$n�Ź����ˡ�\n", me, ob);
	ob->set("closed",1);
	return 1;
}

int do_open(string arg)
{
	object cart;
	object* obj,* team;
	int i,zd=0;
	string * killer;
	
        if(arg != "cart" && arg != "silver cart")
		return notify_fail("��Ҫ��ʲô��\n");
        if( me->query("combat_exp") < 50000000 || userp(me) )
                return notify_fail("��ƾ����㾭�飬����ѧ�������ڳ���\n");
	me = this_player();
	cart=this_object();
	cart->set("closed",0);
	message_vision("$N��$n�Ǵ򿪡�\n", me, this_object());
	if(!checkteam())
		return 1;
		if(me->query_temp("protecting",1) && me->query_temp("protecting",1)==cart)
	{
		me->delete_temp("protecting");
		CHANNEL_D->do_channel( this_object(), "rumor",
		sprintf("%s�����Ե������ڳ��ˣ�"NOR, me->name(1)));
		zd=1;
	}       
	obj = all_inventory(environment(me));
	for(i=0; i<sizeof(obj); i++)
	{
		if (obj[i]!=me && obj[i]->query_temp("protecting")==cart)
		{
			if(zd==1)
				obj[i]->delete_temp("protecting");
			me->kill_ob(obj[i]);
                        me->start_busy(10+random(20));
			obj[i]->kill_ob(me);
		}
	}
	team=(cart->query_temp("team1",1))->query_team();
	for(i=0; i<sizeof(team); i++)
	{
		if(team[i]!=me && team[i]->query_temp("protecting")==cart)
		{
			if(zd==1)
				team[i]->delete_temp("protecting");
			killer=team[i]->query_killer();
			if( member_array(me->query("id"), killer)==-1 )
				killer += ({me->query("id") });
			killer=me->query_killer();
			if( member_array(team[i]->query("id"), killer)==-1 )
				killer += ({team[i]->query("id")});
				
		}
	}
	return 1;
}

int is_closed()
{
	return ((int) this_object()->query("closed"));
}

int do_attack(string arg)
{
	object cart;
	object* obj,* team;
	int i,j;
	string * killer;

	me=this_player();
	cart=this_object();
	if(!checkteam())
		return 1;       
	team=me->query_team();    
	if (sizeof(team) != 0 && (team[0]!=me)) 
		return notify_fail("ֻ�ж����������ָ����ͷ��\n");
	if(!present("jie fei",  environment(me)))
		return notify_fail("���ں���û��Ҫ����ô��\n");
	obj = all_inventory(environment(me));
	for(j=0; j<sizeof(obj); j++)
	{
		if(obj[j]->query("id")=="jie fei" 
		&& objectp(obj[j]->query_temp("target",1)) 
		&& obj[j]->query_temp("target",1)==cart)
			break;
	}
	if(j>=sizeof(obj))
		return notify_fail("���ں���û��Ҫ����ô��\n");
	tell_room(environment(me),me->name()+RED"�ߺ������˽��ڣ���ҿ챣���ڳ�! \n"NOR);
	for(i=0; i<sizeof(obj); i++)
	{
		if((obj[i]->query("id")=="biaotou" || obj[i]->query("id")=="biaoshi") 
		   && obj[i]->query_temp("protecting")==cart)
		{
			if(random(10)>2)
			{
				obj[i]->delete_temp("protecting");
				tell_room(environment(me),obj[i]->name()+
				GRN"�ٺ�һЦ�����ٷ˴��˸��к��������������ˡ�\n"NOR);
				for(j=0;j<sizeof(obj);j++)
				{
					if(j!=i && obj[j]->query_temp("protecting")==cart)
					{       
						obj[j]->kill_ob(obj[i]);
						obj[i]->kill_ob(obj[j]);
					}
				}
				for(j=0; j<sizeof(team); j++)
				{
					if(team[j]!=me && team[j]->query_temp("protecting")==cart)
					{
						killer=obj[i]->query_killer();
						if( member_array(team[j]->query("id"), killer)==-1 )
							killer += ({ team[j]->query("id") });
						killer=team[j]->query_killer();
						if( member_array(obj[i]->query("id"), killer)==-1 )
							killer += ({obj[i]->query("id")});
					}
				}       
			}
			else
			{
				for(j=0;j<sizeof(obj);j++)
				{
					if(obj[j]->query("id")=="jie fei" 
					&& objectp(obj[j]->query_temp("target",1)) 
					&& obj[j]->query_temp("target",1)==cart)
					{       
						obj[j]->kill_ob(obj[i]);
						obj[i]->kill_ob(obj[j]);
					}
				}
			}       
		}
	}
	return 1;
}

int do_driver(string arg)
{
	object* obj,* team,* ob;
	int i,j,lev,attr,maxexp=0;
	string dir,weapon,roomfile,newroomfile;
	mapping skl;
	int * levs;
	object weaponobj,cloneobj,cart,room,newroom,maxplayer;
	mapping skill_status, map_status;
	string *sname, *mname,* tempstr;
	string* weapontype=({ "whip","sword","blade","hammer","axe","stick","throwing","staff",
			      "club" });
	string* weaponfile= ({ "bian","changjian","blade1","chui","dafu","zhubang",
			       "feihuangshi","gangzhang","gun" });
	string* emptyhand=({ "cuff","strike","finger","hand","leg","claw" });
	string* killer,dirname;
	string* clone1=({ "/d/thd/npc/yaoshi","/d/mr/npc/murong-bo","/d/tls/npc/kurong",
			  "/d/dali/wangfu/npc/dzc","/kungfu/class/shaolin/du-nan",
			  "/kungfu/class/gumu/yang","/kungfu/class/gaibang/h7g",
			  "/kungfu/class/emei/mie-jue","/d/huashan/npc/yuebuqun",
			  "/kungfu/class/wudang/zhang"});
	string* pfm_unarmed=({"leg.kuangfeng","blade.yingzhang","finger.sandie",
			      "finger.ciqu","leg.ruying","strike.xiaohun","strike.xiao",
			      "strike.foguang","strike.wuji","cuff.zhen"});
	string* pfm_weapon=({"sword.yuxiao","sword.lianhuan","finger.sandie",
			     "sword.fenglei","sword.sanjue","sword.qixing","stick.wugou",
			     "sword.mie","blade.sanshen","sword.chan"});
	int clonef=0;
	me=this_player();
	cart=this_object();
	if(me->is_busy())
		return notify_fail("������æ�ĺܣ�����ָ���ڳ�ǰ����\n");
	if(!checkteam())
		return 1;       
	team=me->query_team();
	if (sizeof(team)==0) team=({me});
	/*if (sizeof(team) != 0 && (team[0]!=me)) 
		return notify_fail("ֻ�ж����������ָ���ڶ�ǰ����\n");*/
	for(i=0;i<sizeof(team);i++)
	{
		if(team[i]->query("combat_exp")>maxexp)
		{
			maxexp=team[i]->query("combat_exp");
			maxplayer=team[i];
		}
	}
	room=environment(cart);
	roomfile=file_name(room);
	if((arg!="out") && ((roomfile=="/d/city/duchuan") || (roomfile=="/d/xingxiu/boat") ||
		(roomfile=="/d/xingxiu/boat1")))
		return notify_fail("�������ڴ��ϣ�û�ط���ȥ��\n");
	obj = all_inventory(room);
	for(j=0; j<sizeof(obj); j++)
		if(obj[j]->query("id")=="jie fei" && obj[j]->query_temp("target")==cart) break;
	if(j<sizeof(obj))
		return notify_fail("�ٷ���δ��ȥ�������������ߣ���\n");
	switch(arg) {
		case "e":
			dir="east";
			dirname="��";
			break;
		case "w":
			dir="west";
			dirname="��";
			break;
		case "n":
			dir="north";
			dirname="��";
			break;
		case "s":
			dir="south";
			dirname="��";
			break;
		case "ne":
			dir="northeast";
			dirname="����";
			break;
		case "nw":
			dir="northwest";
			dirname="����";
			break;
		case "se":
			dir="southeast";
			dirname="����";
			break;
		case "sw":
			dir="southwest";
			dirname="����";
			break;
		case "u":
			dir="up";
			dirname="��";
			break;
		case "d":
			dir="down";
			dirname="��";
			break;
		case "nu":
			dir="northup";
			dirname="���Ϸ�";
			break;
		case "eu":
			dir="eastup";
			dirname="���Ϸ�";
			break;
		case "su":
			dir="southup";
			dirname="���Ϸ�";
			break;
		case "wu":
			dir="westup";
			dirname="���Ϸ�";
			break;
		case "nd":
			dir="northdown";
			dirname="���·�";
			break;
		case "ed":
			dir="eastdown";
			dirname="���·�";
			break;
		case "sd":
			dir="southdown";
			dirname="���·�";
			break;
		case "wd":
			dir="westdown";
			dirname="���·�";
			break;
		case "enter":
			dir="enter";
			dirname="����";
			break;
		case "out":
			dir="out";
			dirname="����";
			break;
		default:
			dir=arg;
			dirname=arg;
			break;
	}
	if(!room || !room->query("exits/"+dir))
		return notify_fail("��Ҫ������ȥ��\n");
	tell_room(room,HIW"�ڳ����ڶӵĻ�����¡¡����"+dirname+"��ȥ�ˡ�\n"NOR);
	newroomfile=room->query("exits/"+dir);
if(!objectp(newroom=find_object(newroomfile))) newroom=load_object(newroomfile);
	cart->move(newroom);
	cart->add("step", 1);
	for(i=0; i<sizeof(obj); i++)
		if(!userp(obj[i]) && obj[i]->query_temp("protecting")==cart) obj[i]->move(newroom);
	if((roomfile=="/d/city/duchuan") || (newroomfile=="/d/city/duchuan") ||
	   (roomfile=="/d/xingxiu/boat") || (newroomfile=="/d/xingxiu/boat") ||
	   (roomfile=="/d/xingxiu/boat1") || (newroomfile=="/d/xingxiu/boat1"))
		me->move(newroom);
	me->start_busy(random(3)+3);
	tell_room(newroom,HIW"�ڳ����ڶӵĻ�����¡¡��ʻ���ˡ�\n"NOR);
	remove_call_out("fail");
	remove_call_out("check");
	remove_call_out("check2");
	if((newroomfile!="/d/city/duchuan") && (newroomfile!="/d/xingxiu/boat") &&
	   (newroomfile!="/d/xingxiu/boat1") && (random(10)<2) && !newroom->query("no_fight")) {
		skl = maxplayer->query_skills();
		if(!sizeof(skl)) lev=100;
		else {
			levs=values(skl);
			lev=0;
			for(i=0;i<sizeof(levs);i++) {
				if(levs[i]>lev)
				lev=levs[i];
			}
		}
		attr=lev*10;
		jf=new(__DIR__"cateran");
		jf->set("combat_exp",maxplayer->query("combat_exp")+maxplayer->query("combat_exp")/10);
		jf->set_temp("target",cart);//Ҫ���ٵ�Ŀ��

		  jf->set_temp("team_member",maxplayer->query_team());
		i=random(sizeof(clone1));
		if(!objectp(cloneobj=find_object(clone1[i])))
		{
			cloneobj=load_object(clone1[i]);
			clonef=1;
		}
		jf->set("chat_chance_combat", 50);
		jf->set("chat_msg_combat", ({(: perform_action, pfm_unarmed[i] :),
				 (: perform_action, pfm_weapon[i] :) }));
	
		if ( mapp(skill_status = cloneobj->query_skills()) ) {
			sname  = keys(skill_status);

			for(i=0; i<sizeof(skill_status); i++) {
				jf->set_skill(sname[i], lev);
			}
		}

		/* delete and copy skill maps */
	
		map_status = cloneobj->query_skill_map();
		mname  = keys(map_status);

		for(i=0; i<sizeof(map_status); i++) jf->map_skill(mname[i], map_status[mname[i]]);
		if(clonef) destruct(cloneobj);

		ob = all_inventory(maxplayer);
		for(i=0; i<sizeof(ob); i++) {
			if((weapon=ob[i]->query("skill_type")) && map_status[weapon]
			&& !ob[i]->query("treasure") && !ob[i]->query("unique")
			&& !ob[i]->query("imbued")
			&& (ob[i]->query("weapon_prop/damage")>=30) )
			{
				//jf->prepare_skill(weapon,map_status[weapon]);
				weapon=file_name(ob[i]);
				tempstr=explode(weapon,"#");
				weapon=tempstr[0];
				weaponobj= new(weapon);
				if (!weaponobj)  {
					destruct(jf);
					return notify_fail("�쳣����\n");
				}
				weaponobj->move(jf);
				weaponobj->wield(jf);
				break;
			}
		}
		if(i>=sizeof(ob))
		{
			for(i=0;i<sizeof(weapontype);i++)
			{
				if(map_status[weapontype[i]])
				{
					weapon="/clone/weapon/"+weaponfile[i];
					weaponobj= new(weapon);
					if (!weaponobj) {
						destruct(jf);
						return notify_fail("�쳣����\n");
					}
					weaponobj->move(jf);
					weaponobj->wield(jf);
					//jf->prepare_skill(weapontype[i],map_status[weapontype[i]]);
					break;
				}
			}
		}
		for(i=0;i<sizeof(emptyhand);i++)
		{
			if(map_status[emptyhand[i]])
			{
				jf->prepare_skill(emptyhand[i],map_status[emptyhand[i]]);
			}
		}
		jf->set("max_qi",attr+100*random(15));
		jf->set("eff_qi",jf->query("max_qi"));
		jf->set("qi",jf->query("max_qi"));
		jf->set("max_jing",attr+100*random(15));
		jf->set("eff_jing",jf->query("max_jing"));
		jf->set("jing",jf->query("max_jing"));
		jf->set("max_neili",attr+100*random(15));
		jf->set("neili",jf->query("max_neili"));
		jf->set("eff_jingli",attr+100*random(15));
		jf->set("jingli",jf->query("eff_jingli"));
		jf->set("jiali",lev/3+random(31));
		jf->set_temp("apply/damage", lev/2);
		jf->set_temp("apply/armor", lev);
		jf->move(newroom);
		tell_room(newroom,RED"�ݴ���ͻȻ�������ٷˣ�\n"NOR);
		tell_room(newroom,HIR"�ٷ˶�ݺݵ�˵���������ӣ�����Ǯ�ƺú�Т����үү�ɡ�\n"NOR);	      
		for(i=0; i<sizeof(obj); i++)
		{
			if(userp(obj[i]) && obj[i]->query_temp("protecting")==cart)
			{
				obj[i]->kill_ob(jf);
				jf->kill_ob(obj[i]);
			}
		}
		for(i=0; i<sizeof(team); i++)
		{
			if(team[i]!=me && team[i]->query_temp("protecting")==cart)
			{
				killer=jf->query_killer();
				if( member_array(team[i]->query("id"), killer)==-1 )
					killer += ({ team[i]->query("id") });
				killer=team[i]->query_killer();
				if( member_array(jf->query("id"), killer)==-1 )
					killer += ({jf->query("id")});
			}
		}       
		call_out("check", 5, me); 
	} else call_out("fail", 300, cart);
	return 1;       
}

int do_finish(string arg)
{
	object cart,gold,where;
	object* obj,* team;
	int i,j,jl,times;

	me=this_player();
	cart=this_object();
	if( me->is_busy()) return notify_fail("����æ���ء�\n");
	if(!checkteam())
		return 1;       
	//if (sizeof(team)==0) team=({me});
	team=me->query_team();
	if (sizeof(team) != 0 && (team[0]!=me)) 
		return notify_fail("ֻ�ж���������ܾ��������Ƿ��Ѿ�������\n");
	where=environment(me);
	obj = all_inventory(where);
	for(j=0; j<sizeof(obj); j++)
	{
		if(obj[j]->query("id")=="jie fei" 
		&& objectp(obj[j]->query_temp("target",1)) 
		&& obj[j]->query_temp("target",1)==cart)
			break;
	}
	if(j<sizeof(obj))
		return notify_fail("�ٷ˻��ڣ�����������δ��ɣ�\n");
	for(j=0;j<sizeof(team);j++)
	{
		if(!present(team[j]) ||
		team[j]->query_temp("protecting")!=cart)
			break;
	}
	if(j<sizeof(team))
	{
		return notify_fail("��Ķ�Ա��δ���룡\n");
	}
	if(!strcmp((string)me->query_temp("target",1), (string)file_name(where)))
	{
		j=0;
		for(i=0;i<sizeof(team);i++)
			if (team[i]->query_temp("protecting")==cart)
			j++;
		if(j>0)
		{
	       jl= 2499/j + 1;
			times=(time()-me->query_temp("biao_time",1))/60;
			//me->query_temp("biao_time",1) ������ʼʱ��
	    if(times<20)
				times=1;
			else
		times=(times-20)/5+2;
			for(i=0;i<sizeof(team);i++)
				if (team[i]->query_temp("protecting")==cart)
				{
					jl=jl/times+random(31);
		   j = jl/6;
					team[i]->add_busy(2);
					team[i]->add("combat_exp",jl);
					team[i]->add("potential",j);
					team[i]->add("balance", 1000000);
		   if( team[i]->query("potential") > team[i]->query("max_pot"))
		    team[i]->set("potential", team[i]->query("max_pot"));
					//team[i]->add("shen",-adds*2);
					gold=new("/clone/money/gold");
					gold->set_amount(5/times);
					if(gold && !(gold->move(team[i])))
						gold->move(environment(team[i]));
		      tell_object(team[i],HIY"�㱻������"+chinese_number(jl)+"�㾭�飬"+chinese_number(j)+
					"��Ǳ�ܣ�"+chinese_number(5/times)+"���ƽ�\n"NOR);
		      log_file("job/hubiao",sprintf("%s %s(%s)��������������%d��Ǳ��%d�����ھ���%d, step: %d��\n",
			ctime(time())[4..19],team[i]->name(1),capitalize(team[i]->query("id")), jl, j, team[i]->query("combat_exp"), cart->query("step")));
				}
		}
		for(i=0; i<sizeof(obj); i++)
		{
			if(obj[i]->query_temp("protecting")==cart && userp(obj[i]))
			{
				obj[i]->delete_temp("protecting");
			}
		}
		me->dismiss_team();
		CHANNEL_D->do_channel( this_object(), "rumor",
		sprintf("%s���ڶӻ���˳����ɣ�", me->name(1)));
		destructing(cart);
		return 1;
	}
	return notify_fail("�����ڻ�û�е���Ŀ�ĵأ�\n");
}

void check(object me)
{
	object cart;
	object* obj,* team;
	int j;

	cart=this_object();
	obj = all_inventory(environment(cart));
	if(!checkteam())
		return;
	team=(cart->query_temp("team1",1))->query_team();
	for(j=0; j<sizeof(obj); j++)
	{
		if(obj[j]->query("id")=="jie fei" 
		&& objectp(obj[j]->query_temp("target",1)) 
		&& obj[j]->query_temp("target",1)==cart)
			break;
	}
	if(j>=sizeof(obj))
	{
		remove_call_out("fail");
		call_out("fail", 300, cart);
		return;
	}
	for(j=0;j<sizeof(team);j++)
	{
		if(present(team[j], environment(cart)) &&
		team[j]->query_temp("protecting")==cart)
			break;
	}
	if(j>=sizeof(team))
	{
		call_out("check2", 30, me);
	}
	else
	{
		remove_call_out("check");
		call_out("check", 5, me);
	}
}

void check2(object me)
{
	object cart;
	object* obj,* team;
	int j;

	cart=this_object();
	obj = all_inventory(environment(cart));
	if(!checkteam())
		return;
	team=(cart->query_temp("team1",1))->query_team();
	for(j=0; j<sizeof(obj); j++)
	{
		if(obj[j]->query("id")=="jie fei" 
		&& objectp(obj[j]->query_temp("target",1)) 
		&& obj[j]->query_temp("target",1)==cart)
			break;
	}
	if(j>=sizeof(obj))
	{
		remove_call_out("fail");
		call_out("fail", 300, cart);
		return;
	}
	for(j=0;j<sizeof(team);j++)
	{
		if(present(team[j], environment(cart)) &&
		team[j]->query_temp("protecting")==cart)
			break;
	}
	if(j>=sizeof(team))
	{
		for(j=0; j<sizeof(team); j++)
		{
			team[j]->dismiss_team();
			if (team[j]->query_temp("protecting")==cart)
				team[j]->delete_temp("protecting");
		}
		CHANNEL_D->do_channel( this_object(), "rumor",
		sprintf(NOR "%s���ڳ����ٷ˽����ˣ�", cart->query("teamhead")));

		if(objectp(jf=present("jie fei", environment(cart))))
		{
			tell_room(environment(cart),RED"�ٷ˺ٺ�һЦ����������������һƱ�����������ڳ����ˡ�\n"NOR);
		}
		destructing(cart);
	}
	else
	{
		remove_call_out("check");
		call_out("check", 5, me);
	}
}

void destructing(object ob)
{
	object * obj;
	int i;
	object cart=this_object();

	obj = all_inventory(environment(cart));
	for(i=0;i<sizeof(obj);i++)
	{
		if((obj[i]->query("id")=="biaotou" || obj[i]->query("id")=="biaoshi") 
		   && obj[i]->query_temp("protecting")==cart)
		{
			destruct(obj[i]);
		}
		else if(obj[i]->query("id")=="jie fei" 
			&& objectp(obj[i]->query_temp("target",1)) 
			&& obj[i]->query_temp("target",1)==cart)
			destruct(obj[i]);
	}
	destruct(cart);
}

void fail(object ob)
{
	object cart;
	object * team;
	int j;

	cart=this_object();
	if (cart->query_temp("team1")) {
	team=(cart->query_temp("team1"))->query_team();
	for(j=0; j<sizeof(team); j++)
	{
		team[j]->dismiss_team();
		if (team[j]->query_temp("protecting")==cart)
			team[j]->delete_temp("protecting");
	}
	CHANNEL_D->do_channel( this_object(), "rumor",
	sprintf("%s�����ڶӻ���ʧ�ܣ�",cart->query("teamhead")));
	}
	destructing(cart);       
}

int checkteam()
{
	int teams,deathcs;
	object cart,me;
	object* team,* team2;
	int j,fail=0;
	
	cart=this_object();
	teams=cart->query_temp("teams",1);
	team2=({cart});
	if(teams>0)
	{
		me=cart->query_temp("team1",1);
		if(!objectp(me))
			fail=1;
		else
			team2+=({me});
	}
	if(teams>1)
	{
		me=cart->query_temp("team2",1);
		if(!objectp(me))
			fail=1;
		else 
			team2+=({me});
	}
	if(teams>2)
	{
		me=cart->query_temp("team3",1);
		if(!objectp(me))
			fail=1;
		else
			team2+=({me});
	}
	if(teams>3)
	{
		me=cart->query_temp("team4",1);
		if(!objectp(me))
			fail=1;
		else
			team2+=({me});
	}
	team2-=({cart});
	if(!fail)
	{
		team=team2[0]->query_team();
		if (sizeof(team)==0) team=({team2[0]});
		for(j=0;j<teams;j++)
		{
			deathcs=team2[j]->query_temp("death",1);
			if(deathcs<team2[j]->query("death_count"))
				break;
			else if(member_array(team2[j], team)==-1)
				break;
			else if(team2[j]->is_ghost())
				break;
			else if(!team2[j]->is_character())
				break;
		}
		if(j<teams)
			fail=1;
	}
	if(!fail)
		return 1;
	for(j=0; j<sizeof(team2); j++)
	{
		team2[j]->dismiss_team();
		if (team2[j]->query_temp("protecting")==cart)
			team2[j]->delete_temp("protecting");
	}
	CHANNEL_D->do_channel( this_object(), "rumor",
	sprintf("%s���ڳ����ٷ˽����ˣ�", cart->query("teamhead")));
	
	if(objectp(jf=present("jie fei", environment(cart))))
	{
		tell_room(environment(cart),RED"�ٷ˺ٺ�һЦ����������������һƱ�����������ڳ����ˡ�\n"NOR);
	}
	destructing(cart);
	return 0; 
}
