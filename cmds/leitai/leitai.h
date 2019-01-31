void init()
{
	object me;

	me = this_player();
	if (!userp(me)) return;
	if (!wizardp(me) && !me->query_temp("leitai")){
		message_vision("ͻȻ�ɳ�һ˫��ţ���$N����̨�����˳�ȥ��\n", me);
		me->move("/d/city/chmiao");
		message_vision("��������������һ����$N���˴���̨�����˳�����\n", me);
	}
	
	if (!this_object()->query_temp("leitai") 
	&& base_name(me) == "/cmds/leitai/leitaiuser"){
		me->quit(me);
		return;
	}	
	if (userp(me)) message_vision("$N����ææ���߽�����̨��\n", me);
	
	add_action("do_load", "login");
	add_action("do_open", "xinxi");
	add_action("do_tui", "tui");
	add_action("do_leave", "leave");
	add_action("do_ok", "ok");
	add_action("do_action", ({"dazuo", "tuna", "lian", "learn", "du", "steal", "hit",
	                          "kill", "fight", "study", "practice", "exercise", "halt", 
	                          "quit", "save", "throw", "rumor", "tell", "mm", "reply",
	                          "chat", "rumor", "party", "shout", "suicide", "yield"}));
}

int do_action(string arg)
{
	if(!wizardp(this_player())){
		write("��̨��ֻ�ܱ��䣬�벻Ҫ������ص��£�\n");
		return 1;
	}
	else return 0;
}

int open = 0;

int do_open(string arg)
{
	object me = this_player();
	
	if( wiz_level(me) < 3 )
		return notify_fail("ֻ�� (wizard) ���ϵ���ʦ���ܴ���̨��Ϣ��\n");   
	
	if( !arg || arg == "" || arg != "open") 
		return notify_fail("Ŀǰ����̨��Ϣ״���ǣ�"+(open == 0?"close":"open")+"\n");
	
	if( arg == "open" ){
		open = 1;
		message("leitai", HIY +"\n��"+environment(me)->query("short")+"��̨�������Ŵ���̨�����Ϣ����ϣ������������� set block_leitai ��\n\n"NOR, users());
		return notify_fail("�������̨����Ϣ״����\n");
	}
	
	if( arg == "close" ){
		open = 0;
		message("leitai", HIY +"\n��"+environment(me)->query("short")+"��̨�����رմ���̨�����Ϣ��\n\n"NOR, users());
		return notify_fail("��ر�����̨����Ϣ״����\n");
	}
	
	else return notify_fail("������趨��̨��Ϣ״���� open (�����˶��ܿ������) ���� close (ֻ�п�̨���˲ſ������)\n");
}

void end_fight(object me, object ob, string fam)
{
	string fam2, color;
	
	fam2 = ob->query("family/family_name")?ob->query("family/family_name"):"ƽ�����";
        color = ob->query("color")?ob->query("color")+" ":" ";
        fam2 = HIW+fam2+color+NOR+ ob->name(1) + "(" + capitalize(ob->query("id")) + ")";
        message_vision("\n"+fam+" �� "+fam2+" ���ܡ�\n", me, ob);
        if( open > 0 )
        	message("leitai", HIY +"\n��"+environment(me)->query("short")+"��̨�������Ѿ�����ʤ����"+ fam+HIY" �� "+fam2+HIY" ���ܣ�\n\n"NOR, 
        	filter_array(users(), (:  !$1->query("env/block_leitai") :)));
        //Log.
	log_file("leitai",sprintf("%s(%s) �� %s ����̨�ϻ��� %s(%s)��\n", ob->name(1), ob->query("id"), ctime(time()), me->name(1), me->query("id")));
}
       
int start_biwu(object fighter, object fighter2, int num)
{
	object *ob;
	int i;
	
	if( !fighter || environment(fighter) != this_object()){
		if(fighter2) fighter2->quit(fighter2);
		tell_room(this_object(), HIR"\n"+this_object()->query("short")+"������ֹ��\n"NOR);
		return 1;
	}
	
	if( !fighter2 || environment(fighter2) != this_object()){
		if(fighter) fighter->quit(fighter);
		tell_room(this_object(), HIR"\n"+this_object()->query("short")+"������ֹ��\n"NOR);
		return 1;
	}
	
	num++;
	
	if( num <= 1 ){
		fighter->set_temp("last_damage_from", fighter2);
		fighter2->set_temp("last_damage_from", fighter);

		ob = all_inventory(this_object());
		i = sizeof(ob);
		while (i--) {
			if(!userp(ob[i]) && !ob[i]->query_temp("leitai"))
				destruct(ob[i]);
		}	
		tell_room(this_object(), HIR+"\n\t"+this_object()->query("short")+HIR"�ϴ�����"+chinese_number(1)+"�����죡\n\n"NOR);
	}
	
	else if( num >= 3 ){
		message_vision(HIR"ֻ�����������죬$N��$n������ʽ��ʼ��\n"NOR, fighter, fighter2);
		if( open > 0 )
			message("leitai", HIY +"\n��"+this_object()->query("short")+"��̨������λ����ͬ����\n\t\t"
          		NOR+fighter->short(1)+HIY" ��\n\t\t"NOR+fighter2->short(1)+HIY" ������ʽ��ʼ��\n\n"NOR, 
          		filter_array(users(), (:  !$1->query("env/block_leitai") :)));
		else message_vision(HIY +"\n��"+this_object()->query("short")+"��̨������λ����ͬ����\n\t\t"
          		NOR+fighter->short(1)+HIY" ��\n\t\t"NOR+fighter2->short(1)+HIY" ������ʽ��ʼ��\n\n"NOR, 
          		fighter, fighter2);
          		
		fighter->delete("last_death_time");
		fighter2->delete("last_death_time");
		fighter2->kill_ob(fighter);
		fighter->kill_ob(fighter2);
		return 1;
	}
	else tell_room(this_object(), HIR+"\n\t"+this_object()->query("short")+HIR"�ϴ�����"+chinese_number(num)+"�����죡\n\n"NOR);

	remove_call_out("start_biwu");
	call_out("start_biwu", 4 , fighter, fighter2, num);
	return 1;
}

int do_ok()
{
	object ob, me = this_player();

	if(!me->query_temp("leitai") || base_name(me) != "/cmds/leitai/leitaiuser")
		return notify_fail("������ֻ����̨�����ѡ�ֿ��á�\n");

        if(me->query_temp("leitai") == 2)
		return notify_fail("���Ѿ�������ս�ˡ�\n");
		
	me->set_temp("leitai", 2);
	if(!objectp(ob = this_object()->query_temp("fighter"))){
		this_object()->set_temp("fighter", me);
		message_vision("\n$N���˸��ϣ�"+RANK_D->query_self(me)+"�Ѿ�׼�����ˣ�Ը�����κ���ս��\n", me);
	}
	
	else if(environment(ob) != this_object()){
		ob->quit(ob);
		this_object()->set_temp("fighter", me);
		message_vision("\n$N���˸��ϣ�"+RANK_D->query_self(me)+"�Ѿ�׼�����ˣ�Ը�����κ���ս��\n", me);
	}
	else {
		this_object()->delete_temp("fighter");
		message_vision("\n$N��$n���˸��ϣ�"+RANK_D->query_self(me)+"ð������ս"+RANK_D->query_respect(ob)+"��\n", me, ob);
		start_biwu(me, ob, 0);
	}
	
	return 1;
}

void leaving(object me)
{
	if(!me || me->is_fighting() ) return;
	if(!me->query_temp("leitai") && base_name(me) != "/cmds/leitai/leitaiuser")
		return;
	message_vision(HIW"\n$Nһ���߰�����̬����Ȼû�˸�����ս������"+RANK_D->query_self(me)+"���������޵��ˣ�\n\n"NOR, me);
        me->die();
	return;
}	
	
int do_leave()
{
	object me = this_player();

	if(!me->query_temp("leitai") && base_name(me) != "/cmds/leitai/leitaiuser")
		return notify_fail("������ֻ����̨�����ѡ�ֿ��á�\n");
		
	message_vision(HIW"\n$N��̾��һ������"+RANK_D->query_self(me)+"�������ˣ���Ը���䣡\n\n"NOR, me);
        me->die();
	return 1;
}


int do_tui(string arg)
{
	object ob;

	if (!arg) return notify_fail("��Ҫ��˭��\n");
	if (!ob = present(arg,this_object()) )
		return notify_fail("�Ҳ��� "+arg+" �����ҡ�\n");
	if( !userp(ob))
		return notify_fail("�Ҳ��� "+arg+" �����ҡ�\n");
	if (!ob->query_temp("leitai") || base_name(ob) != "/cmds/leitai/leitaiuser")
		return notify_fail(ob->name()+"����ͨ������;��������̨�����ܱ��Ƴ���̨��\n");
        if( wiz_level(this_player()) < 3)
		return notify_fail("ֻ�� (wizard) ���ϵ���ʦ���ܽ����Ƴ���̨��\n");        

	message_vision("$Nˣ�˸�̫������$nһ���Ƴ�����̨��\n", this_player(), ob);
	ob->quit(ob);
	return 1;
}

int load_user(object player)
{
	object user;
	string arg, color;

	arg = player->query("id");
	
	if (!arg 
	|| this_object()->query_temp("leitai") > 1
	|| base_name(player) == "/cmds/leitai/leitaiuser")
		return 0;  

	seteuid(arg);
	user = new("/cmds/leitai/leitaiuser");   // ȥ����save()����̨�е�һ�кͱ����޹ء�
	user->set_name("", ({ arg }));
	if(!user->restore()) {
		destruct(user);
		write("User Restore Error����֪ͨ��ʦ��\n");
		return 0;
	}

	user->setup();		
	user->set_temp("leitai", 1);    
	exec(user, player);
	user->set("link_ob", player);
	user->set_temp("link_ob", player->query_temp("link_ob"));
	this_object()->add_temp("leitai", 1);
	user->move(this_object());
	user->clear_condition();
	user->reincarnate();
	user->delete_temp("combat_yield");
	user->set("channels", ({ "rumor", "err" }) );
	tell_object(user, YEL"����������̨��Ŀǰ�������״̬�С�\n"NOR"
��Ҫ���������Ʒ������ "YEL"NA"NOR" ��
�����׼���������"YEL" OK "NOR"��
�����Ҫ�������������"YEL" LEAVE "NOR"��\n\n");

	arg = user->query("family/family_name")?user->query("family/family_name"):"ƽ�����";
	color = user->query("color")?user->query("color")+" ":" ";
        arg = HIW+arg+NOR+" "+color + user->name(1) + NOR "(" + capitalize(user->query("id")) + ")";
	tell_room(this_object(), arg + YEL"���������̨��\n\n"NOR, ({ user }));
	player->set_temp("apply/short", ({player->name()+"("+player->query("id")+")"YEL" <������> "NOR}));
	player->set_leader(0);
	call_out("leaving", 50, user);
	return 1;
}


int do_load(string arg)
{
	object me, user, ob;
	string arg1, arg2;

	if (!arg) return 0;
	if(sscanf(arg, "%s with %s", arg1, arg2)!=2){
		if(!me = find_player(arg))
			return notify_fail("�����ʽ: login <player name1> with <player name2>��\n");
		else return load_user(me);
	}
	
	me = this_player();

	if( this_object()->query_temp("leitai") > 1 )
		return notify_fail("�������ڱ����أ����ȵ����Ƿֳ�ʤ����˵�ɡ�\n");  
		
	if( wiz_level(me) < 3 )
		return notify_fail("ֻ�� (wizard) ���ϵ���ʦ��������̨login����player��\n");        
        if (wiz_level(me) < wiz_level(arg1))
		return notify_fail("�㲻��װ����ʦ�������ߵ���ҡ�\n");

	ob = find_player(arg2);
	if ( !ob ) return notify_fail("��˭Ϊ���������̨��\n");
	if(ob->query_temp("leitai")
	|| base_name(ob) == "/cmds/leitai/leitaiuser")
		return notify_fail(ob->name()+"���ڱ����̨�����С�\n");

	seteuid(arg1);
	user = new("/cmds/leitai/leitaiuser");   // ȥ����save()����̨�е�һ�кͱ����޹ء�
	user->set_name("", ({ arg1 }));
	if(!user->restore()) {
		destruct(user);
		return notify_fail("�������ĸ���ҵĿ���������̨��\n");;
	}
	if(!environment(ob)->query("no_fight"))
	     	ob->move("/d/city/chmiao");  // ��ֹ����ʱ����ɱ
	user->setup();
	if (wiz_level(user) > wiz_level(me)){
		user->quit(user);
		return notify_fail("�㲻��װ����ʦ�������ߵ���ҡ�\n");
	}

	user->set_temp("leitai", 1);       
	exec(user, ob);
	user->set("link_ob", ob);
	user->set_temp("link_ob", ob->query_temp("link_ob"));
	this_object()->add_temp("leitai", 1);
	user->move(this_object());
	user->clear_condition();
	user->reincarnate();
	user->delete_temp("combat_yield");
	user->set("channels", ({ "rumor" , "err"}) );
	tell_object(user, YEL"�����"+user->name()+"������̨��Ŀǰ�������״̬�С�\n"NOR"
��Ҫ������ӱ��������� "YEL"NA"NOR" ��
�����׼���������"YEL" OK "NOR"��
�����Ҫ�������������"YEL" LEAVE "NOR"��\n\n");
	tell_room(environment(user),YEL+ob->query("name")+"����"+user->name()+"���������̨��\n\n"NOR, ({ user }));
	ob->set_temp("apply/short", ({ob->name()+"("+ob->query("id")+")"YEL" <������> "NOR}));  
	return 1;
}
