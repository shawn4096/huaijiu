// view.h

#define LONG "���Ǳ�����Ĺۿ�����,��ɽ�˺��������ݱ�ı�������\n�ڽ��ŵľ����š�ǰ����һ���ܴ������̨,����һֱ����������\n������ָ��Ϊ����Ա����ҿ��������л���Ҫ�ۿ��ĳ��ء�\n"
void init()
{
	object me = this_player();

         if (userp(me) && !wizardp(me))  me->start_busy(10);
        add_action("do_kan",({"kan"}));
        if (!wiz_level(me) || wiz_level(me) < 3) return;
        add_action("do_control",({"control"}));
}

int do_kan(string arg)
{
        object me = this_player();
        object ob;

        if (!wizardp(this_player()) && this_player()->query("id") != query("controller"))
		return notify_fail("���ֲ��ǿ���Ա,��ô����Ƶ��?!\n");
        if (!arg)
                return notify_fail("����kan xxxx��̨��\n");
	if (arg != "snooper1"
	 && arg != "snooper2"
         && arg != "snooper3"
         && arg != "snooper4"
         && arg != "snooper5"
         && arg != "snooper6")
        	return notify_fail("����kan xxxx��̨��ѡ���У�snooper1,snooper2,snooper3,snooper4,snooper5,snooper6��\n");
        if (!query("start"))
                return notify_fail("���仹û��ʼ�أ����Ҷ���\n");
        if (!query(arg))  return notify_fail("Ŀǰ���Ƶ����û��ʲô�ÿ��ģ�\n");
        set_temp("b4",query_temp("view"));
        set_temp("view",arg);
        message_vision(HIW"\n$N��Ƶ��������"+arg+"�ϡ�\n"NOR,me);
//        if (!objectp(ob = find_object("/cmds/leitai/bwdh/obj/"+arg+".c")))  return notify_fail("��������ʧ�����ش���������ʦ���棡\n");
        if (query(arg) == "die") {
                tell_room(this_object(),HIY"����Ļ�� ��Ƶ���Ѿ�������\n          ���ڽ��Զ���ת��"+ob->query_temp("b4")+"Ƶ����\n");
                set_temp("view",query_temp("b4"));
                return 1;
        }
        tell_room(this_object(),HIY"\n����Ļ����Ƶ����������ȫ��ֱ��"+find_player(query(arg))->name(1)+"("+query(arg)+")�ı�������ӭ�տ���\n"NOR);
        return 1;
}

int do_control(string arg)
{
	object me = this_player();

	if (!arg)
        return notify_fail("ָ���ʽ: control <ID|none>��\n");
        if (arg == "none") {
                tell_object(me,"���ջ������д����Ŀ���Ȩ��\n");
                load_object("/cmds/leitai/bwdh/view1")->delete("controller");
                load_object("/cmds/leitai/bwdh/view2")->delete("controller");
                load_object("/cmds/leitai/bwdh/view3")->delete("controller");
                load_object("/cmds/leitai/bwdh/view4")->delete("controller");
                load_object("/cmds/leitai/bwdh/view5")->delete("controller");
                load_object("/cmds/leitai/bwdh/view6")->delete("controller");
                return 1;
        }
	if (!query("controller"))
		message_vision(HIR"\n$N������Ȩ������"+arg+"��\n",me);
	else
		message_vision(HIR"\n$N������Ȩ��"+query("controller")+"������"+arg+"��\n",me);
	set("controller",arg);
	return 1;
}
