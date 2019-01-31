// yuelao.c ��������

inherit NPC;

int do_register();
int do_zuomei(string);
int do_divorce(string);

void create()
{
        set_name("��������", ({ "yuexiao laoren", "yuelao", "laoren" }));
        set("long", 
                "�����Ǵ�˵��ר�����ϵ�����Ե�����������ˡ�\n"
                "��������⣬��ü�԰ף��������Ѳ�֪�ж������ˡ�\n"
                "���������Ƕ�����һ���飬�������һ����������������������Щʲô��\n");
        set("gender", "����");
        set("age", 3000);
        set("attitude", "friendly");
        set("str", 500);
        set("int", 500);
        set("con", 300);
        set("per", 25);
        
        set("max_qi", 10000);
        set("max_jing", 10000);
        set("combat_exp", 20000000);

        set_skill("force", 500);
        set_skill("dodge", 800);
        set_skill("unarmed", 500);
        set_skill("parry", 800);
        set_skill("literate", 900);

        setup();
}

void init()
{
        add_action("do_register", "register");
        add_action("do_register", "jiehun");
        add_action("do_divorce", "divorce");
        add_action("do_divorce", "lihun");
        add_action("do_zuomei", "zuomei");
}

int do_register()
{
        object me, who, meiren;
        me=this_player();

        if (!me->query_temp("marry")) {
                command("say �ף�������Ե����û���������ѽ ... ..."); 
                command("say ���������Ȼ�ȥ�����Ҹ����ҵ�������Ե�����ɡ�");
                return 1;
        }
        if (me->query("gender")=="Ů��") {
                command("say �ţ������δ�����ǰ����");
                return 1;
        }
        if (!objectp(who=present(me->query_temp("marry"),environment(me)))) {
                command("say �ţ������Ե�����ˣ�����Ϊʲô���δ����ûһ������");
                command("say ������δ���޵����������Ҳ���Ϊ������ɵǼ�������");
                return 1;
        }
        if (who->query_temp("marry")!=me) {
                command("say �����������δ����Ϊ���ִ�Ӧ��������ˣ�����");
                command("say �����뿪ʲô��Ц�������������������");
                return 1;
        }
        if (!who->query_temp("meiren")) {
                command("say
����Ե��׻�˵�ĺá���ĸ֮����ý��֮�ԡ�������̶���޸�ĸ����Ҳ���ˡ�");
                command("say ������ý��֮�ԣ���Ҳ̫�����ˡ�");
                command("say ����ȥ�Ҹ�ý�����ɣ������ڴ���֤���Ҳ���Ϊ�������顣");
                return 1;
        }
        if (!objectp(meiren=present(who->query_temp("meiren"),environment(me)))) {
                command("say �ţ�����˶�������ˣ�������ý�������Ķ�ȥ����");
                command("say ���ý���ҵ���������Ҳ���Ϊ������ɵǼ�������");
                return 1;
        }

        command("say �����������ü��ˣ�һ���뱸�������Ϊ���ǵǼǣ�");
        write("�������˵�ͷ����Ե�����˷���д��Щʲô��\n");
        command("say ��ϲ����ϲ��");
        command("chat ����������������");
        command("chat "+me->name()+"��"+who->name()+"��"+meiren->name()+"��ý������ϲ����Ե����λ����������֤��");
        command("chat ��ף��λ��ͷ���ϣ��������ӡ�");
        
        who->delete_temp("marry");
        who->delete_temp("meiren");
        who->set("marry/id",me->query("id"));
	who->set("marry/name",me->query("name"));
        me->delete_temp("marry");
        me->set("marry/id",who->query("id"));
	me->set("marry/name",who->query("name"));
	new("/clone/misc/marry-token")->move(me);
	new("/clone/misc/marry-token")->move(who);
	message_vision("$N��$n�����˶������\n", me, who);

        return 1;
}

int do_zuomei(string arg)
{
        object me, who;
        me=this_player();

        if (!arg || !objectp(who=present(arg,environment(me)))) {
                tell_object(me,"��Ҫ��˭��ý��\n");
                return 1;
        }
        if (who->query("gender")=="����") {
                tell_object(me, "�ţ���ý��ΪŮ����ý��");
                return 1;
        }
        if (!who->query_temp("marry")) {
                tell_object(me,"�ţ�����û�����鰡����Ϲ��ʲô�壿����\n");
                return 1;
        }
	if (me==who->query_temp("marry")) {
		write("�Լ����Լ���ý����̫�ðɣ�\n");
		return 1;
	}
        command("say "+RANK_D->query_respect(me)+"ԭ���"+who->name()+"��ý��");
        command("say ����ǳ���֮�������°����ü��ˣ�����ͼ�¼����");
        who->set_temp("meiren", me);
        return 1;
}

int do_divorce(string arg)
{
        object me,who;
        me=this_player();

        if (!arg) {
                write("������˭��飿\n");
                return 1;
        }
                
        if (!me->query("marry")) {
                command("say �����û����飡");
                return 1; }
        if (me->query("gender")=="����") {
                if (me->query("marry/id") != arg) {
                        command("say ���˸������������ӣ�");
                        return 1; }
                if (!who=find_player(arg)) {
                        command("say �Բ������������ڲ������ϣ����ܰ����������");
                        return 1; }
                if (!me->query_temp("divorcing")) {
                        command("say �����㵱���������������������ǣ�������������һ�Ρ�");
                        me->set_temp("divorcing",1);
                        return 1; }
		me->delete_temp("divorcing");
                me->delete("marry");
		me->add("divorce", 1);
                who->delete("marry");
                tell_object(who, me->name(1)+"�������ˡ�\n");
        }
        else {
                if (me->query("marry/id") != arg) {
                        command("say ���˸����������ɷ�");
                        return 1; }
                if (!who=find_player(arg)) {
                        command("say �Բ������ɷ����ڲ������ϣ����ܰ����������");
                        return 1; }
                if (!me->query_temp("divorcing")) {
                        command("say �����㵱������������ɷ�������ǣ�������������һ�Ρ�");
                        me->set_temp("divorcing",1);
                        return 1; }
		me->delete_temp("divorcing");
                me->delete("marry");
		me->add("divorce", 1);
                who->delete("marry");
                tell_object(who, me->name(1)+"�������㣬��֪�Ǹ�˭˽��ȥ�ˡ�\n");
        }
        command("say �� ... ...");
        command("chat �ӽ�����"+me->name(1)+"��"+who->name(1)+"�Ͳ����Ƿ����ˡ�");
        command("chat ��һ׮ʧ�ܵĻ������� ... ... ");
	if (present("yu pei", me)) present("yu pei", me)->lost(me);
	if (present("xiang nang", me)) present("xiang nang", me)->lost(me);
	if (present("yu pei", who)) present("yu pei", who)->lost(who);
	if (present("xiang nang", who)) present("xiang nang", who)->lost(who);
        return 1;
}
