// qqren.c 裘千仞
#include <ansi.h>
inherit NPC;
int ask_qiubai();
string do_change();
inherit F_MASTER;
#include "tz_job1.c"

void create()
{
        set_name("裘千仞", ({ "qiu qianren", "qiu", "qianren", "ren"}));
        set("nickname", "铁掌水上漂");
        set("long", 
        "他就是威震川湘的铁掌帮的帮主-铁掌水上漂裘千仞。\n"
        "他是一个白须老头，身穿黄葛短衫，右手挥着一把大蒲扇。\n");
        set("gender", "男性");
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

        create_family("铁掌帮", 14, "帮主");

        set("inquiry", ([
                       "name" : "老夫便是“铁掌水上漂”裘千仞，你问老夫姓名有什么事么？\n",
                       "here" : "这里就是铁掌帮的总坛所在，你如没事，不要四处乱走，免招杀身之祸！！！\n",
                       "上官剑南" : (: ask_qiubai :),
                       "交换" : (: do_change :),
                       "工作" : (: ask_job1 :),
//                       "护帮" : (: ask_job2 :),
                       "工具" : "你去工具房找要吧！", 
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

        if(shen > 0 && myfam["family_name"] == "铁掌帮" 
    && myfam["master_name"] != "上官剑南"){
         command("say 老子最看不惯你这种自命大侠的人，来人啦！把这个家伙给我臭揍一顿。");
        write(HIC"只见二个彪形大汉在你左右二面一夹，你顿时动弹不得。\n" NOR);
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
        if (!fam || fam["family_name"] !="铁掌帮")
           return RANK_D->query_respect(me)+"不会是想转派吧？BBB 可是不会准许的。\n";
        if( me->query("tz/rec") )
           return RANK_D->query_respect(me)+"已经换过了。\n";
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

        return  "好了，你的斧法，笔法已经成功转换为刀法了。\n" ;
}
void attempt_apprentice(object ob)
{
        object me  = this_object();
        mapping fam = ob->query("family");

        if ((int)ob->query("shen") >= -50000) {
                command("hehe");
                command("say 我裘千仞可不收心慈手软的人做徒弟。");
                return;
                }        
        if(fam["master_name"] == "上官剑南"){
                command("ah");
                command("grin" + ob->query("id"));
                command("say 上官帮主不是早已故世多年了嘛？");
                command("say "+RANK_D->query_respect(ob)+"原来是老帮主关门弟子啊，失敬。"+RANK_D->query_self(me)+"怎敢再收你为徒？"); 
                return;
                }
        if ((int)ob->query_skill("guiyuan-tunafa", 1) < 120) {
                command("say 要学更为高深的武功，必须有高深的内功修为。"); 
                command("say " + RANK_D->query_respect(ob)+"是否还应该在归元吐纳法上多下点功夫？");
                return;
                }
        if ((int)ob->query_str() < 28) {
                command("say 想学我的铁掌掌法，必须要有足够的力量。");
                command("say 在臂力方面，"+RANK_D->query_respect(ob)+"是否还嫌差了点？");
                return;
                }   
                command("say 好吧，我就收下你了。希望你苦练铁掌神功，将之发扬光大。");
                command("recruit " + ob->query("id"));
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                add("apprentice_available", -1);
           ob->set("title", HIY"铁掌帮第十四代帮主门下"NOR);
        ob->set("class","brigand");

}
int ask_qiubai()
{
        say("他是我师父。我在十三岁那年曾救过他，之后他感恩图报，将全\n"
            "身武功倾囊相受。可惜十年前，他在湖北遭人围攻而死！唉！\n");
        return 1;
}
