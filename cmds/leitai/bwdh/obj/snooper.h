
#define __BWDH__ "/cmds/leitai/bwdh/"

object* obj = ({load_object(__BWDH__"view1"),
                load_object(__BWDH__"view2"),
                load_object(__BWDH__"view3"),
                load_object(__BWDH__"view4"),
                load_object(__BWDH__"view5"),
                load_object(__BWDH__"view6")});

void init()
{
        object ob = this_player();
        
        if (userp(ob) && !wizardp(ob)) {
                tell_object(ob,"��ͻȻ��һ�����ߣ���ѽ����ѽ���������������˿͵ꡣ\n");
                ob->move("/d/city/kedian");
                message_vision(RED"\nͻȻ�����ˡ���һ����$N�ӿ��е����������պ����ڵ�С����ͷ�ϡ�\n"NOR,ob);
                return;
        }
}


void check_online(object me, string arg)
{
        object ob;
        string pl1, pl2, pl3;
        int i;
        
        if (!me->query("snoop") || me->query("snoop") != arg)
                return;
        if (!(ob = find_player(arg)))
        {
                pl1 = me->query("p/i1")==arg?"":me->query("p/i1")+"��";
                pl2 = me->query("p/i2")==arg?"":me->query("p/i2");
                pl3 = me->query("p/i3")==arg?"":"��"+me->query("p/i3");
        message("channel:chat","������ͨ�桿��"+me->query("pp")+"����" +arg + "��������Ŀǰʣ��"+pl1+pl2+pl3+"\n",users());
		snoop(me);
	        for (i=0;i<sizeof(obj);i++)
            obj[i]->set(me->query("id"),"die");
        }
        call_out("check_online",1,me,arg);
}       

int do_snoop(string arg)
{
        object ob = this_player();
        object me = this_object();
        object objj;
	int i;

        if (!arg)
                return 0;
        seteuid(geteuid(ob));
//      objj = new(LOGIN_OB);
//      objj->set("name",arg);
//      if (!objj->restore())
        if (FINGER_D->finger_user(arg) == "û�������ҡ�\n")
                return notify_fail("û�������ҡ�\n");
//      destruct(objj);

        for (i=0;i<sizeof(obj);i++)
        obj[i]->set(me->query("id"),arg);
		
        if (objj = find_player(arg))
        {
                snoop(me,objj);
                remove_call_out("check_online");
                call_out("check_online",1,me,arg);
                return 1;
        }
        else
                return notify_fail("�����Ҳ����ߡ�\n");
}

void receive_snoop(string str)
{
        object env = environment();
        int i;

        if (!env) return;
                
        str = "1\n" + str;
        for (i=0;i<sizeof(obj);i++) {
            if (!obj[i]->query_temp("view")) continue;
            if (obj[i]->query_temp("view") == this_object()->query("id"))
                tell_room(obj[i],CYN"����Ļ��"CYN+ str+ NOR);
        }
}
