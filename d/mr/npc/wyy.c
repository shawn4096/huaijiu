//wang.c

inherit NPC;

void create()
{
        set_name("������", ({ "wang yuyan", "wang" }));
        set("long", "�����ü�Ϊ��ò,һ˫�۾���������.\n");
        set("nickname", "�����޲�֪");
           set("title","��٢��ɽׯׯ��֮Ů");
        set("gender", "Ů��");
        set("unique", 1);
        set("age", 20);
        set("attitude","friendly");
        set("str", 30);
        set("dex", 30);
        set("con", 30);
        set("int", 30);
        set("per", 30);
        set("max_qi", 5000);
        set("max_jing", 1000);
        set("neili", 3000);
        set("max_neili", 3000);

        setup();
        carry_object(__DIR__"obj/skirt1")->wear();        carry_object(__DIR__"obj/shoe")->wear();        carry_object(__DIR__"obj/green_silk")->wear();
}

void init()
{
        add_action("lingwu","ask");
}

int lingwu(string arg)
{
        object me=this_player();
        object where = environment(me);
        string special;
        int bl,sl;
        string name;
        if (!arg) return 0;
        if (!sscanf(arg, "%s about %s", name, arg)) return 0;
        if (!id(name)) return 0;

        if (!me->query("luohan_winner")) return notify_fail("�㼶�𲻹��������ڴ�����\n");
        write( "������������̹��ڡ�" + to_chinese(arg) + "�������ʡ�\n");
        if (me->is_busy() || me->is_fighting()) {
                command("say ����æ���ء�");
                return 1;
        }
        if(where->query("lingwu") != 1 )
                return notify_fail("��ֻ�����������������������书��\n");
        if (!(special=me->query_skill_mapped(arg))) {
                if (arg == to_chinese(arg))
                        command("say ��" + arg + "����ʲô�书����ô��û��˵����");
                else
                        command("say ��ֻ�ܴ�������⼼���и���ָ�㡣");
		me->add_busy(1);
                return 1;
        }
        if (!me->query_skill(arg,1)) {
                command("say �㲻�����ּ��ܡ�");
		me->add_busy(1);
                return 1;
        }
    if (arg == "force" && (int)me->query_skill("force",1)<200) {
                command("shake");
                command("say ��Ŀǰ��Ϊ��ǳ�������Լ���������ڹ���");
		me->add_busy(1);
                return 1;
        }
        if((int)me->query("potential", 1) < 1 ) {
		me->add_busy(1);
                write("���ʵս�еõ���Ǳ���Ѿ������ˡ�\n");
		return 1;
	}
        bl=me->query_skill(arg,1);
        if (bl > me->query("jing") || me->query("jing")*100/me->query("max_jing") < 50) {
                me->receive_damage("jing",bl/2);
                command("say " + RANK_D->query_respect(me) + "����Ϣһ�°ɡ�");
		me->add_busy(1);
                return 1;
        }
        sl=me->query_skill(special,1);
        if (bl > sl) {
                command("say " + RANK_D->query_respect(me) + "��"+to_chinese(special)+"���費�����Ҳ���ָ�������һ���"+to_chinese(arg)+"��");
		me->add_busy(1);
                return 1;
        }
        write("������" + name() + "��ָ�㣬��"+to_chinese(arg)+"�����������һ�㡣\n");
        me->receive_damage("jing",bl/5*3);
if(random(5)>2) me->add("potential",-1);
me->improve_skill(arg,(int)(me->query_skill("literate",1))/3+5);
if(me->query("age")<30)me->improve_skill(arg,30-me->query("age"));
if(me->query("age")>60)me->improve_skill(arg,me->query("age")-60);
        return 1;
}

void kill_ob(object ob)
{
        ob->remove_killer(this_object());
        remove_killer(ob);
        command("peace " + ob->query("id"));
}

