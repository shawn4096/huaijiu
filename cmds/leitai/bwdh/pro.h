// Purpose : Ready to fight
// Creator : Numa@Sj 2000-5-4 11:28

int start_trace(object me, object local)
{
	object obj = this_object();
	object ob;
	
	ob = load_object(__DIR__"obj/snooper"+local->query("snoop"));
    ob->set("pp",obj->query("party"));
    if (ob->query("pp") == local->query_temp("p1")) {
		ob->set("p/i1",local->query_temp("p1/i1"));
		ob->set("p/i2",local->query_temp("p1/i2"));
		ob->set("p/i3",local->query_temp("p1/i3"));
	}
	else {
		ob->set("p/i1",local->query_temp("p2/i1"));
		ob->set("p/i2",local->query_temp("p2/i2"));
		ob->set("p/i3",local->query_temp("p2/i3"));
	}
		
	ob->do_snoop(me->query("id"));
	return 1;
}

int do_ok()
{
	object me = this_player();
	object ob = this_object();
    object *pl = ({me,me,me}), *obje, obj, local;
	string *group;
	int i, ready = 0;
	
	if (!me->query_temp("leitai"))
		return notify_fail("���ֲ��μӱ��䣬��ô������ģ���Ŷ��������ʦ��\n");
        if (me->query_temp("ready"))
                return notify_fail("���Ѿ�׼�����ˣ���okʲôѽ����\n");
	if (!ob->query("packet"))
		return notify_fail("��֪ͨ��ʦ�����ݶ�ʧ����\n");
    if (ob == load_object(__DIR__"xiuxishi1"))
		obj = load_object(__DIR__"xiuxishi2");
	else
		obj = load_object(__DIR__"xiuxishi1");
	me->set_temp("ready",1);
	group = explode(ob->query("packet")," ");
	for (i=0;i<sizeof(group);i++) {
		if (!(pl[i] = present(group[i],ob)))
			return notify_fail(group[i]+"���ڴ˵أ���\n");
		if (pl[i]->query_temp("ready"))
			ready += 1;
	}
        ob->set("ready",ready);
	local = load_object(__DIR__"ctrl");
	if (!local->query("snoop"))
		local->set("snoop",1);
	else
		local->add("snoop",1);
	call_out("start_trace", 1, me, local);
	if (ready == 3) {
		message_vision(HIY"\n$N����һ�´�ң�����Ҷ�׼������Ӧս�����Ǵ��һ�����������ߣ���\n"HIR"�Ȱգ�������ȥ�ƴ��ţ����Ǵ�����˿������\n"NOR,me);
		if (obj->query("ready") == 3) {
			tell_room(ob,HIG"������֮�������ż����򿪣�����������£�\nһ�����˽���ɽׯ��ֻҪ������������˳��������˿ɼ���������\n��������ʤ�����������Ŵ���ɽׯ�ڵ�һ�顣\n"NOR);
			tell_room(obj,HIG"������֮�������ż����򿪣�����������£�\nһ�����˽���ɽׯ��ֻҪ������������˳��������˿ɼ���������\n��������ʤ�����������Ŵ���ɽׯ�ڵ�һ�顣\n"NOR);
			tell_room(local,HIR"\n����ʦ��֯�� ���ߵ���Ҷ���׼����Ӧս������(press button)���ţ�\n"NOR);
			obje = ({load_object(__BWDH__"view1"),
		        	load_object(__BWDH__"view2"),
        			load_object(__BWDH__"view3"),
		        	load_object(__BWDH__"view4"),
        			load_object(__BWDH__"view5"),
        			load_object(__BWDH__"view6")});
        		for(i=0;i<sizeof(obje);i++)
				obje[i]->set("start",1);
			return 1;
		}
		tell_room(ob,HIG"������֮������һ����δ׼�����������Ժ\n"NOR);
		tell_room(obj,HIG"������֮������"+ob->query("party")+"���Ѿ�׼����������ץ��ʱ�䣡��\n"NOR);
		tell_room(local,HIR"\n����ʦ��֯�� ��"+ob->query("party")+"���Ѿ�׼��������\n"NOR);
		return 1;
	}
	message_vision(GRN"\n$N������һ������װ���������Ѿ�׼����Ӧս�ˣ�\n"NOR, me);
	return 1;
}

int do_chuanyin(string arg)
{
	object me = this_player();
	object ob = this_object();
	object obj;
	
    if (ob == load_object(__DIR__"xiuxishi1"))
		obj = load_object(__DIR__"xiuxishi2");
	else
		obj = load_object(__DIR__"xiuxishi1");	

        if (me->query_temp("stop_cy"))
                return notify_fail("������ʹ��ǧ�ﴫ����\n");
	if (!arg)
        tell_room(obj,HIR"��ǧ�ﴫ����"HIY+ob->query("party")+"��"+me->name(1)+"�����һ����\n"NOR);
	else
        tell_room(obj,HIR"��ǧ�ﴫ����"HIY+ob->query("party")+"��"+me->name(1)+"˵����"+arg+"��\n"NOR);
	tell_object(me,"���Ļ����Ѵ�����"+obj->query("party")+"�ķ��䡣\n");
	me->set_temp("stop_cy",1);
    call_out("start_cy",4,me);
	return 1;
}

void start_cy(object me)
{
	if (!me)
		return;
	me->delete_temp("stop_cy");
}
