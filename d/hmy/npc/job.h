//*************************************** find target ***************//
int do_ready()
{
        object ob = this_object();
        object *ulist, selected;
        string hostage_n,hostage_i,hostage_w,myfam;
        mapping npcgroup;
        int i, j;
        
        ulist = filter_array(objects(), (: userp :));
        ulist = filter_array(ulist, (: $1->query("combat_exp") > 1000000 && $1->query("shen") > 500000 && !$1->query_temp("be_saved") && !wizardp($1) :));

        if (1==1) {
//        if (sizeof(ulist) < 1 || random(sizeof(ulist)) < 10 || random(10) > 4) {
                npcgroup = npclist[random(sizeof(npclist))];
                hostage_n = npcgroup["name"];
                hostage_i = npcgroup["id"];
                hostage_w = npcgroup["where"];
                myfam = npcgroup["family"];
                ulist = objects( (: clonep :) );
                for (i=0;i<sizeof(ulist);i++)
                        if (ulist[i]->query("id") == hostage_i) {
                                tell_room(environment(ulist[i]),"ͻȻ����֪��ʲô�ط����������ħ��ɱ�֣���ȭ���Ű�" + hostage_n + "�򵹺�̧���ˡ�\n");
                                ulist[i]->revive(1);
                                ulist[i]->reicarnate();
                                selected = ulist[i];
                                remove_call_out("do_check_where");
                                call_out("do_check_where", 1, ulist[i]);
                                break;
                        }
                if (!objectp(selected)) {
                        call_out("do_ready",1);
                        return 1;
                }
        }

// ������������ҳ� exp > 1000000 ,+shen > 500000 �ģ�Ȼ��������һ��ȥ����
        else {
		j = random(sizeof(ulist));
                message_vision("ͻȻ����֪��ʲô�ط����������ħ��ɱ�֣���ȭ���Ű�$N�򵹺�̧���ˡ�\n",ulist[j]);
                hostage_n = ulist[j]->query("name");
                hostage_i = ulist[j]->query("id");
                hostage_w = base_name(environment(ulist[j]));
                myfam = ulist[j]->query("family/family_name");
                ulist[j]->set_temp("be_saved",1);
                ulist[j]->unconcious();
                selected = ulist[j];

                if (!objectp(selected)) {
                        call_out("do_ready",1);
                        return 1;
                }
        }
        selected->move(__HMY__"jail");
        selected->set("startroom", __HMY__"jail");
        selected->set_temp("hostage/where",hostage_w);
        ob->set("hostage/name",hostage_n);
        ob->set("hostage/id",hostage_i);
        ob->set("hostage/where",hostage_w);
        ob->set("hostage/family",myfam);
        ob->set("hostage/target",selected);
        ob->set("hostage/ready",1);
        call_out("do_fail", 1800, ob);
        return 1;
}

void do_check_where(object ob)
{
        object room;

        if (environment(ob) != (room = load_object(__HMY__"jail"))) {
                tell_room(environment(ob), HIR"\nͻȻ���Ա߳�����˼���������̵��ӣ�����"+ob->name()+"HIR��ݺݵ�˵�������ܣ������������ܣ�\n\n"NOR);
                ob->move(room);
                remove_call_out("do_check_where");
                call_out("do_check_where", 1, ob);
                return;
        }
        remove_call_out("do_check_where");
        call_out("do_check_where", 1, ob);
}

//*************************************** give job 1 ***************//
int ask_renzhi()
{
        object me = this_object();
        object ob = this_player();
        object ob1, ob2;
        
        if (ob->query_condition("job_busy")) {
                command("say " + RANK_D->query_respect(ob) + "������æ���أ�");
                return 1;
        }

        if (ob->query_condition("hostage_busy")) {
                command("say " + RANK_D->query_respect(ob) + "������Ӫ�ȹ����ʣ��������ˡ�");
                return 1;
        }

        if (!me->query("hostage/ready") ) {
                command("say �����������Ȼ��Ϊħ�̣���Ҳ����������ץ������ʿ�ģ�");
                return 1;
        }
        if (me->query("hostage/gived") >= 2 ) {
                command("say �Ѿ�����ȥ�����ˣ�");
                return 1;
        }
        
        if (base_name(environment(me)) != __HMY__"pingding/kefang") {
		command("say ��˵ʲô�أ�");
		return 1;
        }
        if (ob->query("combat_exp")<1500000) {
                command("say �����ʿ���ʮ��Σ�յģ��ҿ������ƺ��޴������ɣ�");
                return 1;
        }
/*
        if (ob->query("shen")<0) {
                command("say ������¶�׹⣬�����Ƕ������������İɣ�");
                return 1;
        }
*/

	command("say �ֽ񶫷����ܽ�"HIY
                + me->query("hostage/family") + CYN"��"HIY
                + me->query("hostage/name") + "("
                + me->query("hostage/id") + ")"CYN"ץȥ�������ʣ��������Ҫ��취�����ȳ�����");

	if (me->query("hostage/gived") == 0) {
		me->set("pl1/name",ob->query("name"));
		me->set("pl1/id",ob->query("id"));
		me->set("hostage/gived", 1);
		command("say ����Σ�շǷ�������ֻ����һ���ˣ�����������ɣ�����Ҫ����һ�����");
		return 1;
	}
    if (!(ob1 = present(me->query("pl1/id"),environment(me)))) {
        command("say �ף�"+me->query("pl1/name")+"("+me->query("pl1/id")+")��ô�����ˣ�");
		me->set("hostage/gived", 1);
		me->set("pl1/name",ob->query("name"));
		me->set("pl1/id",ob->query("id"));
		command("say ����������һ���˴�ɣ�");
		return 1;
	}
	if (ob == ob1) {
		command("? " + ob->query("id"));
		command("say ����ô������ȥ�Ҵѽ����");
		return 1;
	}
        me->set("hostage/gived", 2);
        me->set("pl2/name",ob->query("name"));
	me->set("pl2/id",ob->query("id"));

// �������
	ob2 = ob;
	if (random(2)) {
		ob2 = ob1;
		ob1 = ob;
	}

// to pl1
        ob1->set_temp("hostage/partner",ob2->query("id"));
        ob1->set_temp("hostage/hostage_n",me->query("hostage/name"));
        ob1->set_temp("hostage/hostage_i",me->query("hostage/id"));
        ob1->apply_condition("hostage1",40+random(20));
        ob1->apply_condition("hostage_busy",300);

// to pl2
        ob2->set_temp("hostage/partner",ob1->query("id"));
        ob2->set_temp("hostage/hostage_n",me->query_temp("hostage/name"));
        ob2->set_temp("hostage/hostage_i",me->query_temp("hostage/id"));
        ob2->apply_condition("hostage11",50+random(20));
        ob2->apply_condition("hostage_busy",300);

        
        command("say �������ǵ���ҪĿ����Ҫ��̽�ú�ľ�µ���ʵ��Ȼ���������ᣡ");
        ob1->set_temp("hostage/job_1",1);
        command("whisper " + ob1->query("id") + " ������ȥ��ħ�̳���ͯ���ۣ��������������������ܵ���Ϣ��");
        
        ob2->set_temp("hostage/job_1",2);
        command("whisper " + ob2->query("id") + " ������ȥ�������Ѻ�ľ��Ҫ��������������š�");

//make a log
        log_file("job/HMY_1",sprintf("%s %s(%s)[exp %d]��%s(%s)[exp %d]��ʼӪ��%s(%s)��\n", ctime(time())[4..19], ob1->name(1), ob1->query("id"), ob1->query("combat_exp"), 
        				ob2->name(1), ob2->query("id"), ob2->query("combat_exp"), me->query("hostage/name"), me->query("hostage/id")));
	remove_call_out("waiting");
	call_out("waiting", 600, me);
        return 1;
}

int waiting(object me)
{
        object one, two;

        one = find_player(me->query("pl1/id"));
        if (!one)
                one = find_living(me->query("pl1/id"));
        if (one) {
                one->delete_temp("hostage");
                one->apply_condition("hostage_busy",80+random(20));
        }
        two = find_player(me->query("pl2/id"));
        if (!two)
                two = find_living(me->query("pl2/id"));
        if (two) {
                two->delete_temp("hostage");
                two->apply_condition("hostage_busy",80+random(20));
        }
        me->set("hostage/gived",0);
        command("say �ף�"+me->query("pl1/name")+"("+me->query("pl1/id")+")��"
        	+me->query("pl1/name")+"("+me->query("pl1/id")+")��ô�������������������׶༪���ˣ�");
        command("sigh");
	return 1;
}


//*************************************** job 2 ***************//
// ����Ҫ���job1        
int ask_jiuren()
{
        object me = this_object();
        object ob = this_player();
        object ob1, ob2;
        
        if (base_name(environment(me)) != __HMY__"pingding/kefang") {
		command("say ��˵ʲô�أ�");
		return 1;
        }
        
        if (me->query("hostage/gived") >= 4) {
                command("say �Ѿ�����ȥ�����ˣ�");
                return 1;
        }

        if (me->query("hostage/gived") <= 2) {
                command("say ����Ϊ����֮������������Ҫ��ʲô���أ���");
                return 1;
        }

        if (!me->query("hostage/ready") ) {
                command("say ���Ѿ����ˣ������Ѿ������˾����ˣ�");
                return 1;
        }

        if (ob->query("combat_exp")<1500000) {
                command("say �����ʿ���ʮ��Σ�յģ��ҿ������ƺ��޴������ɣ�");
                return 1;
        }
        if (ob->query("shen")<0) {
                command("say ������¶�׹⣬�����Ƕ������������İɣ�");
                return 1;
        }

	if (me->query("pl1/id") == ob->query("id")) {
		ob1 = ob;
		if (!(ob2 == present(me->query("pl2/id"),environment(me)))) {
			command("�ף�"+me->query("pl2/name")+"("+me->query("pl2/id")+")��ô�����ˣ�");
			command("say ����ȥ�������ɣ����ǵ�ʱ����ȣ�");
			return 1;
		}
	}
	else if (me->query("pl2/id") == ob->query("id")) {
		ob2 = ob;
		if (!(ob1 == present(me->query("pl1/id"),environment(me)))) {
			command("�ף�"+me->query("pl1/name")+"("+me->query("pl1/id")+")��ô�����ˣ�");
			command("say ����ȥ�������ɣ����ǵ�ʱ����ȣ�");
			return 1;
		}
	}
	else {
		command("say ����Σ�շǷ��������ڵ�"+me->query("pl1/name")+"("+me->query("pl1/id")+")��"
       			+me->query("pl1/name")+"("+me->query("pl1/id")+")���ǵ���Ϣ��");
		return 1;
	}

// �������	
	if (random(2)) {
		ob = ob1;
		ob1 = ob2;
		ob2 = ob;
	}

        ob1->apply_condition("hostage2",100 + random(20));
        ob2->apply_condition("hostage2",100 + random(20));
        
        me->set("hostage/gived",4);
        
        ob1->set_temp("hostage/job_2", 1);
        message_vision("$N����ͷ��������һ�ᡣ\n",me);
        command("whisper " + ob1->query("id") + " ������ȥ����ɱ�����أ�׼����"+ me->query("hostage/name") +"��");
        command("whisper " + ob1->query("id") + " ����������ں���ǽ�ϣ��ƶ�(push)��Ϳ��Խ�ȥ�ˡ�");
        
        ob2->set_temp("hostage/job_2", 2);
        command("whisper " + ob2->query("id") + " �����ڴ�����ȥ����ͤ���鷿��Կ�ף�С�ĵ㣬���������ˡ�");
        command("say ���ˣ����ڳ���ȥӪ��" + me->query("hostage/family") + "��" + me->query("hostage/name") + "���ҵ������ǵĺ���Ϣ��");
//make a log
        log_file("job/HMY_2",sprintf("%s %s(%s)[exp %d]��%s(%s)[exp %d]��ʼӪ��%s(%s)��\n", ctime(time())[4..19], ob1->name(1), ob1->query("id"), ob1->query("combat_exp"), 
        				ob2->name(1), ob2->query("id"), ob2->query("combat_exp"), me->query("hostage/name"), me->query("hostage/id")));
	remove_call_out("waiting");
	call_out("waiting", 1000, me);

        return 1;
}

int do_fail(object me)
{
        object ob, room;
        object one, two;

        room = load_object(__HMY__"jail");
        ob = present(me->query("hostage/id"),room);
        if (!ob) {
                message_vision(CYN"$N�����������ԭ��" 
                + me->query("hostage/family") + "��"
                + me->query("hostage/name") + "�Ѿ����˾����ˣ�\n"NOR,me);
                return 1;
        }
        tell_object(ob,"��������ͻȻ���ˣ��߽���һ��ħ��ɱ�֣�������˳�ȥ��\n");
        ob->move(me->query("hostage/where"));
        tell_room(environment(ob),"����ħ�̵���Ѻ��" + ob->name() + "���˹�����\n",({ob}));
        message_vision(HIY"\n��ͷ��ת�������Ķ�$N˵��������������������ҷ���������Ժ�������ģ���˵�������Ц�������첽�뿪�ˡ�\n"NOR,ob);

        if (me->query("hostage/pl1")) {
        one = find_player(me->query("hostage/pl1"));
        if (!one)
                one = find_living(me->query("hostage/pl1"));
        if (one) {
                one->delete_temp("hostage");
                one->apply_condition("hostage_busy",80+random(20));
        }
        }
        if (me->query("hostage/pl2")) {
        two = find_player(me->query("hostage/pl2"));
        if (!two)
                two = find_living(me->query("hostage/pl2"));
        if (two) {
                two->delete_temp("hostage");
                two->apply_condition("hostage_busy",80+random(20));
        }
        }

	me->delete("hostage");
        me->set("hostage/gived", 0);
        remove_call_out("do_check_where");
        remove_call_out("do_ready");
	call_out("do_ready", 900);
	return 1;
}

int do_letout()
{
        object obj,room,me = this_object(),ob = this_player();

        if (!wizardp(ob) && ob->query("id")!= "numa")
                return 1;
        if (!me->query("hostage/where") || !me->query("hostage/id")) {
                command("say ����û�����ʱ�ץ�߰ɣ���ʹ������ʦ��Ҳ���ܿ�������Цѽ��");
                command("kick numa");
                command("giggle");
                return 1;
        }
        room = load_object(__HMY__"jail");
        if (!objectp(obj = present(me->query("hostage/id"),room))) {
                command("say �����Ѿ����ų�ȥ��ѽ��");
                command("lean numa");
                return 1;
        }
        obj->move(obj->query_temp("hostage/where"));
        command("say "+ me->query("hostage/id") +"�Ѿ������ķԸ��ų�ȥ�ˡ�");
        if (userp(obj))
                tell_object(obj,GRN"��ӯӯ�����������˵�������������ҷ����ȥ�ģ�����߰ɣ����ٱ�ץס�ˣ�\n"NOR);
        message_vision(HIY"ͻȻ��һ�������$N��Ȼ������������Ӵ���ɵɵ�������Ǳ��Ż��ˡ�\n"NOR,obj);
        return 1;
}
