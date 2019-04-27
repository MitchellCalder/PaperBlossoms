#include <QtTest>
#include <QCoreApplication>
#include <QDir>

// add necessary includes here
#include "../PaperBlossoms/src/dataaccesslayer.h"
#include "../PaperBlossoms/src/dataaccesslayer.cpp"

class TestMain : public QObject
{
    Q_OBJECT

public:
    TestMain();
    ~TestMain();

    DataAccessLayer* dal;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();
    void test_dal_importCSV();
    void test_dal_qsl_getclans();
    void test_dal_qsl_getfamilies();
    void test_dal_qsl_getfamilyrings();
    void test_dal_qs_getclandesc();
    void test_dal_qs_getfamilydesc();

};

TestMain::TestMain()
{

    QString targetpath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    if(QDir(targetpath).exists()){
        QMessageBox msgBox;
        msgBox.setText("TESTING");
        msgBox.setInformativeText("Do you want to remove local data for testing?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        const int ret = msgBox.exec();

        if(ret == QMessageBox::Yes){
            QDir target = targetpath;
            target.removeRecursively();
        }
    }

        dal = new DataAccessLayer();

}

TestMain::~TestMain()
{

}

void TestMain::initTestCase()
{
}

void TestMain::cleanupTestCase()
{

}

void TestMain::test_case1()
{
        QVERIFY(true);
}

void TestMain::test_dal_importCSV(){

    bool success = true;
    foreach(QString tablename, dal->user_tables){

        success &= dal->importCSV(":/exports/export_sample", tablename);
    }
    QVERIFY(success);
}

void TestMain::test_dal_qsl_getclans()
{
        QStringList clans = dal->qsl_getclans();
        QVERIFY(!clans.isEmpty());
}

void TestMain::test_dal_qsl_getfamilies(){
    QStringList clans = dal->qsl_getclans();
    foreach(QString clan, clans){
        QStringList families = dal->qsl_getfamilies(clan);
        QVERIFY(!families.empty());
    }
}

void TestMain::test_dal_qsl_getfamilyrings(){
    QStringList clans = dal->qsl_getclans();
    foreach(QString clan, clans){
            QStringList families = dal->qsl_getfamilies(clan);
            foreach(QString family, families){
                QStringList rings = dal->qsl_getfamilyrings(family);
                QVERIFY(!rings.empty());
            }
     }

}
void TestMain::test_dal_qs_getclandesc(){
    //have already imported a database that includes a crane desc
    QString desc = dal->qs_getclandesc("Crane");
    QVERIFY(!desc.isEmpty());

}
void TestMain::test_dal_qs_getfamilydesc(){
    //have already imported a database that includes a crane desc
    QString desc = dal->qs_getfamilydesc("Kakita");
    QVERIFY(!desc.isEmpty());
}

QTEST_MAIN(TestMain)

#include "tst_testmain.moc"
