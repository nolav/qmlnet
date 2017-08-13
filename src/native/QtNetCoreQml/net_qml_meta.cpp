#include "net_qml_meta.h"
#include <private/qmetaobjectbuilder_p.h>

QMetaObject *metaObjectFor(NetTypeInfo *typeInfo)
{
    if (typeInfo->metaObject) {
            return reinterpret_cast<QMetaObject *>(typeInfo->metaObject);
    }

    QMetaObjectBuilder mob;
    mob.setSuperClass(&QObject::staticMetaObject);
    mob.setClassName("TestQmlImport");
    mob.setFlags(QMetaObjectBuilder::DynamicMetaObject);

    for(int index = 0; index <= typeInfo->GetMethodCount() - 1; index++)
    {
        NetMethodInfo* methodInfo = typeInfo->GetMethod(index);
        mob.addMethod(methodInfo->GetMethodName().c_str());
    }

    QMetaObject *mo = mob.toMetaObject();

    typeInfo->metaObject = mo;
    return mo;
}

GoValueMetaObject::GoValueMetaObject(QObject *value, NetInstance *instance, NetTypeInfo *typeInfo)
    : value(value), instance(instance), typeInfo(typeInfo)
{
    //d->parent = static_cast<QAbstractDynamicMetaObject *>(priv->metaObject);
    *static_cast<QMetaObject *>(this) = *metaObjectFor(typeInfo);

    QObjectPrivate *objPriv = QObjectPrivate::get(value);
    objPriv->metaObject = this;
}

int GoValueMetaObject::metaCall(QMetaObject::Call c, int idx, void **a)
{
    return -1;
}

void GoValueMetaObject::activatePropIndex(int propIndex)
{
    // Properties are added first, so the first fieldLen methods are in
    // fact the signals of the respective properties.
    int relativeIndex = propIndex - propertyOffset();
    activate(value, methodOffset() + relativeIndex, 0);
}