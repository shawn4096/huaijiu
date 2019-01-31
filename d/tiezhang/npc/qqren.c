// qqren.c ��ǧ��
#include <ansi.h>
inherit NPC;
int ask_qiubai();
string do_change();
inherit F_MASTER;
#include "tz_job1.c"

void create()
{
        set_name("��ǧ��", ({ "qiu qianren", "qiu", "qianren", "ren"}));
        set("nickname", "����ˮ��Ư");
        set("long", 
        "����������������ư�İ���-����ˮ��Ư��ǧ��\n"
        "����һ��������ͷ�����Ƹ���������ֻ���һ�Ѵ����ȡ�\n");
        set("gender", "����");
        set("age", 60);
        set("attitude", "peaceful");
        set("unique", 1);
        set("shen_type", -1);
        set("str", 35);
        set("int", 30);
        set("con", 28);
        set("dex", 35);
        
        set("max_qi",7000);
        set("max_jing", 5000);
        set("max_neili",16000);
        set("eff_jingli", 4000);
        set("jiali", 100);
        set("combat_exp", 2900000);
        set("score", 400000);

        set_skill("force", 300);
        set_skill("guiyuan-tunafa", 300);
        set_skill("dodge", 330);
        set_skill("shuishangpiao", 330);
        set_skill("strike", 300);
        set_skill("tiezhang-zhangfa", 300);
        set_skill("parry", 300);
        set_skill("literate", 180);
        set_skill("blade", 200);
        set_skill("liuye-daofa", 200);
        set_skill("tiezhang-xinfa",200);    

        map_skill("force", "guiyuan-tunafa");
        map_skill("dodge", "shuishangpiao");
        map_skill("strike", "tiezhang-zhangfa");
        map_skill("parry", "tiezhang-zhangfa");
        map_skill("blade", "liuye-daofa");
        prepare_skill("strike", "tiezhang-zhangfa");

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "strike.zhangdao" :),
                (: perform_action, "strike.tianlei" :),
                (: perform_action, "strike.judu" :),
                (: perform_action, "strike.heyi" :)
        }));
        set_temp("apply/armor", 40);
        set_temp("apply/damage", 30);
        set_temp("apply/attack", 40);

        create_family("���ư�", 14, "����");

        set("inquiry", ([
                       "name" : "�Ϸ���ǡ�����ˮ��Ư����ǧ�������Ϸ�������ʲô��ô��\n",
                       "here" : "����������ư����̳���ڣ�����û�£���Ҫ�Ĵ����ߣ�����ɱ��֮��������\n",
                       "�Ϲٽ���" : (: ask_qiubai :),
                       "����" : (: do_change :),
                       "����" : (: ask_job1 :),
//                       "����" : (: ask_job2 :),
                       "����" : "��ȥ���߷���Ҫ�ɣ�", 
                ]));
        setup();
        carry_object(__DIR__"obj/mayi")->wear();
}
void init()
{
        object me, ob;
        ::init();
        ob = this_player();
        me = this_object();
        if (interactive(ob = this_player()) && !is_fighting()) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }       
       add_action("do_task","task"); 
     
}
/*
void greeting(object me)
{
        mapping myfam;
        int shen;
        myfam = (mapping)me->query("family");
        shen = me->query("shen");

        if(shen > 0 && myfam["family_name"] == "���ư�" 
    && myfam["master_name"] != "�Ϲٽ���"){
         command("say ��������������������������ˣ���������������һ���ҳ���һ�١�");
        write(HIC"ֻ���������δ��������Ҷ���һ�У����ʱ�������á�\n" NOR);
//        me->move("/d/tiezhang/jianyu");
me->unconcious();
me->set("eff_qi",1);
me->set("qi",1);
        me->unconcious();        
        }
}
*/
string do_change()
{
        object me = this_player();
        mapping fam;
        int basic, special;
        fam = me->query("family");
        if (!fam || fam["family_name"] !="���ư�")
           return RANK_D->query_respect(me)+"��������ת�ɰɣ�BBB ���ǲ���׼��ġ�\n";
        if( me->query("tz/rec") )
           return RANK_D->query_respect(me)+"�Ѿ������ˡ�\n";
        basic = me->query_skill("axe",1);
        if (me->query_skill("brush",1) > basic) basic = me->query_skill("brush",1);
        special = me->query_skill("lietian-fu",1);
        if (me->query_skill("yingou-bifa",1) > special) special = me->query_skill("yingou-bifa",1);

           me->delete_skill("axe");
           me->delete_skill("lietian-fu");
           me->delete_skill("brush");
           me->delete_skill("yingou-bifa");
           me->set_skill("blade", basic);
           me->set_skill("liuye-daofa", special);
           me->set("tz/rec", 1);

        return  "���ˣ���ĸ������ʷ��Ѿ��ɹ�ת��Ϊ�����ˡ�\n" ;
}
void attempt_apprentice(object ob)
{
        object me  = this_object();
        mapping fam = ob->query("family");

        if ((int)ob->query("shen") >= -50000) {
                command("hehe");
                command("say ����ǧ��ɲ����Ĵ����������ͽ�ܡ�");
                return;
                }        
        if(fam["master_name"] == "�Ϲٽ���"){
                command("ah");
                command("grin" + ob->query("id"));
                command("say �Ϲٰ����������ѹ����������");
                command("say "+RANK_D->query_respect(ob)+"ԭ�����ϰ������ŵ��Ӱ���ʧ����"+RANK_D->query_self(me)+"����������Ϊͽ��"); 
                return;
                }
        if ((int)ob->query_skill("guiyuan-tunafa", 1) < 120) {
                command("say Ҫѧ��Ϊ������书�������и�����ڹ���Ϊ��"); 
                command("say " + RANK_D->query_respect(ob)+"�Ƿ�Ӧ���ڹ�Ԫ���ɷ��϶��µ㹦��");
                return;
                }
        if ((int)ob->query_str() < 28) {
                command("say ��ѧ�ҵ������Ʒ�������Ҫ���㹻��������");
                command("say �ڱ������棬"+RANK_D->query_respect(ob)+"�Ƿ��Ӳ��˵㣿");
                return;
                }   
                command("say �ðɣ��Ҿ��������ˡ�ϣ������������񹦣���֮������");
                command("recruit " + ob->query("id"));
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                add("apprentice_available", -1);
           ob->set("title", HIY"���ư��ʮ�Ĵ���������"NOR);
        ob->set("class","brigand");

}
int ask_qiubai()
{
        say("������ʦ��������ʮ�����������ȹ�����֮�����ж�ͼ������ȫ\n"
            "���书�������ܡ���ϧʮ��ǰ�����ں�������Χ������������\n");
        return 1;
}
